/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>
#include <algorithm>

//Project Includes
#include "corvusoft/restless/session.hpp"
#include "corvusoft/restless/request.hpp"
#include "corvusoft/restless/response.hpp"
#include "corvusoft/restless/settings.hpp"
#include "corvusoft/restless/detail/session_impl.hpp"

//External Includes
#include <corvusoft/network/tcpip.hpp>

//System Namespaces
using std::end;
using std::bind;
using std::begin;
using std::string;
using std::search;
using std::size_t;
using std::uint16_t;
using std::function;
using std::multimap;
using std::error_code;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_error_code;
using std::chrono::milliseconds;
using std::dynamic_pointer_cast;

//Project Namespaces
using corvusoft::restless::detail::SessionImpl;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;
using corvusoft::core::RunLoop;
using corvusoft::network::TCPIP;
using corvusoft::network::Adaptor;
using corvusoft::protocol::Frame;

namespace corvusoft
{
    namespace restless
    {
        Session::Session( void ) : m_pimpl( new SessionImpl )
        {
            m_pimpl->runloop = make_shared< RunLoop >( );
            m_pimpl->adaptor = make_shared< TCPIP >( m_pimpl->runloop );
            m_pimpl->runloop->start( );
        }
        
        Session::Session( const shared_ptr< Adaptor > adaptor, const shared_ptr< RunLoop > runloop ) : m_pimpl( new SessionImpl )
        {
            m_pimpl->adaptor = adaptor;//what if the user hands in nullptr, what if mixed. how to share runloop?
            m_pimpl->runloop = runloop;
        }
        
        Session::~Session( void )
        {
            return;
        }
        
        void Session::close( const function< error_code ( const shared_ptr< Session >, const error_code status ) > completion_handler )
        {
            if ( completion_handler == nullptr ) return;
            
            m_pimpl->adaptor->close( [ this, completion_handler ]( auto adaptor, auto status )
            {
                if ( status ) return completion_handler( shared_from_this( ), status );
                
                status = m_pimpl->adaptor->teardown( );
                return completion_handler( shared_from_this( ), status );
            } );
        }
        
        void Session::open( const shared_ptr< Settings > settings, const function< error_code ( const shared_ptr< Session >, const error_code ) > completion_handler )
        {
            if ( completion_handler == nullptr ) return;
            
            m_pimpl->settings = settings;
            auto status = m_pimpl->adaptor->setup( m_pimpl->settings );
            if ( status )
                completion_handler( shared_from_this( ), status );
            else
                m_pimpl->adaptor->open( m_pimpl->settings, [ this, completion_handler ]( auto, auto status )
            {
                return completion_handler( shared_from_this( ), status );
            } );
        }
        
        void Session::open( const string& address, const uint16_t port, const function< error_code ( const shared_ptr< Session >, const error_code ) > completion_handler )
        {
            m_pimpl->settings = make_shared< Settings >( );
            m_pimpl->settings->set_port( port );
            m_pimpl->settings->set_address( address );
            
            open( m_pimpl->settings, completion_handler );
        }
        
        void Session::send( const shared_ptr< Request > request, const function< error_code ( const shared_ptr< Session >, const shared_ptr< const Response >, const error_code ) > completion_handler )
        {
            if ( request == nullptr or completion_handler == nullptr ) return;
            
            auto headers = request->get_headers( );
            auto default_headers = get_default_headers( );
            headers.insert( begin( default_headers ), end( default_headers ) );
            request->set_headers( headers );
            
            auto data = m_pimpl->disassemble( request );
            m_pimpl->adaptor->produce( data, [ this, completion_handler ]( auto, auto, auto status )
            {
                if ( status )
                    return completion_handler( shared_from_this( ), nullptr, status );
                    
                m_pimpl->receive( shared_from_this( ), completion_handler );
                return status;
            } );
        }
        
        void Session::yield( const string data, const function< error_code ( const shared_ptr< Session >, const error_code ) > completion_handler )
        {
            yield( make_bytes( data ), completion_handler );
        }
        
        void Session::yield( const Bytes data, const function< error_code ( const shared_ptr< Session >, const error_code ) > completion_handler )
        {
            if ( completion_handler == nullptr ) return;
            
            m_pimpl->adaptor->produce( data, [ this, completion_handler ]( auto, auto, auto status )
            {
                return completion_handler( shared_from_this( ), status );
            } );
        }
        
        void Session::fetch( const size_t length, const function< error_code ( const shared_ptr< Session >, const Bytes, const error_code ) > completion_handler )
        {
            if ( completion_handler == nullptr ) return;
            
            if ( m_pimpl->data.size( ) >= length )
            {
                auto iterator = begin( m_pimpl->data );
                auto data = Bytes( iterator, iterator + length );
                m_pimpl->data.erase( iterator, iterator + length );
                completion_handler( shared_from_this( ), data, error_code( ) );
                return;
            }
            
            m_pimpl->adaptor->consume( [ this, length, completion_handler ]( auto adaptor, auto data, auto status )
            {
                m_pimpl->data.insert( end( m_pimpl->data ), begin( data ), end( data ) );
                
                if ( status )
                    completion_handler( shared_from_this( ), data, status );
                else
                    fetch( length, completion_handler );
                    
                return status;
            } );
        }
        
        void Session::fetch( const string delimiter, const function< error_code ( const shared_ptr< Session >, const Bytes, const error_code ) > completion_handler )
        {
            fetch( make_bytes( delimiter ), completion_handler );
        }
        
        void Session::fetch( const Bytes delimiter, const function< error_code ( const shared_ptr< Session >, const Bytes, const error_code ) > completion_handler )
        {
            if ( completion_handler == nullptr ) return;
            
            auto start = begin( m_pimpl->data );
            auto position = search( start, end( m_pimpl->data ), begin( delimiter ), end( delimiter ) );
            auto found = position not_eq end( m_pimpl->data );
            if ( found )
            {
                auto data = Bytes( start, position );
                m_pimpl->data.erase( start, position + delimiter.size( ) );
                completion_handler( shared_from_this( ), data, error_code( ) );
                return;
            }
            
            m_pimpl->adaptor->consume( [ this, delimiter, completion_handler ]( auto adaptor, auto data, auto status )
            {
                m_pimpl->data.insert( end( m_pimpl->data ), begin( data ), end( data ) );
                
                if ( status )
                    completion_handler( shared_from_this( ), data, status );
                else
                    fetch( delimiter, completion_handler );
                    
                return status;
            } );
        }
        
        void Session::observe( const shared_ptr< Request > request, const function< milliseconds ( const shared_ptr< const Response >, const error_code ) > event_handler, const function< error_code ( const shared_ptr< Session >, const shared_ptr< const Response >, const error_code ) > reaction_handler )
        {
            if ( event_handler == nullptr or reaction_handler == nullptr ) return;
            
            send( request, [ this, request, event_handler, reaction_handler ]( auto session, auto response, auto status )
            {
                auto next_probe_time = event_handler( response, status );
                if ( next_probe_time == milliseconds::zero( ) )
                    reaction_handler( session, response, status );
                else
                    m_pimpl->runloop->launch_in( next_probe_time, [ this, request, event_handler, reaction_handler ]( auto status )
                {
                    observe( request, event_handler, reaction_handler );
                    return status;
                }, "corvusoft::restless::observer" );
                
                return status;
            } );
        }
        
        multimap< string, string > Session::get_default_headers( void ) const
        {
            multimap< string, string > values = m_pimpl->default_headers;
            
            for ( const auto& header : m_pimpl->computed_headers )
                values.emplace( header.first, header.second( ) );
                
            return values;
        }
        
        void Session::set_default_header( const string& name, const string& value )
        {
            m_pimpl->default_headers.emplace( name, value );
        }
        
        void Session::set_default_header( const string& name, const function< string ( void ) >& value )
        {
            if ( value == nullptr )
                m_pimpl->default_headers.emplace( name, "" );
            else
                m_pimpl->computed_headers.emplace( name, value );
        }
        
        void Session::set_default_headers( const multimap< string, string >& values )
        {
            m_pimpl->computed_headers.clear( );
            m_pimpl->default_headers = values;
        }
    }
}
