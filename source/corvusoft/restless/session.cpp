/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>

//Project Includes
#include "corvusoft/restless/session.hpp"
#include "corvusoft/restless/request.hpp"
#include "corvusoft/restless/response.hpp"
#include "corvusoft/restless/settings.hpp"
#include "corvusoft/restless/detail/session_impl.hpp"

//External Includes

//System Namespaces
using std::bind;
using std::string;
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
            m_pimpl->adaptor = adaptor;
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
            
            m_pimpl->runloop->wait( );
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
            if ( m_pimpl->settings == nullptr )
                m_pimpl->settings = make_shared< Settings >( );
            m_pimpl->settings->set_port( port );
            m_pimpl->settings->set_address( address );
            
            open( m_pimpl->settings, completion_handler );
        }
        
        void Session::send( const shared_ptr< Request > request, const function< error_code ( const shared_ptr< Session >, const error_code ) > completion_handler )
        {
            if ( completion_handler == nullptr ) return;
            
            auto data = m_pimpl->disassemble( request );
            m_pimpl->adaptor->produce( data, [ this, completion_handler ]( auto, auto, auto status )
            {
                return completion_handler( shared_from_this( ), status );
            } );
        }
        
        void Session::send( const shared_ptr< Request > request, const function< error_code ( const shared_ptr< Session >, const shared_ptr< const Response >, const error_code ) > completion_handler )
        {
            if ( completion_handler == nullptr ) return;
            
            auto data = m_pimpl->disassemble( request );
            fprintf( stderr, "Sending: %.*s\n", data.size( ), data.data( ) );
            m_pimpl->adaptor->produce( data, [ this, completion_handler ]( auto, auto, auto status )
            {
                if ( status ) return completion_handler( shared_from_this( ), nullptr, status );
                
                receive( completion_handler );
                return status;
            } );
        }
        
        void Session::receive( const function< error_code ( const shared_ptr< Session >, const shared_ptr< const Response >, const error_code ) > completion_handler )
        {
            if ( completion_handler == nullptr ) return;
            
            m_pimpl->adaptor->consume( [ this, completion_handler ]( auto, auto data, auto status )
            {
                //fprintf( stderr, "called receive: %.*s\n", data.size( ), data.data( ));
                if ( status ) return completion_handler( shared_from_this( ), nullptr, status );
                fprintf( stderr, "called receive: %.*s\n", data.size( ), data.data( ) );
                auto response = make_shared< Response >( );//m_pimpl->assemble( data );
                if ( not m_pimpl->builder->is_finalised( ) )
                    return make_error_code( std::errc::resource_unavailable_try_again );
                    
                if ( response == nullptr ) return completion_handler( shared_from_this( ), nullptr, make_error_code( std::errc::bad_message ) );
                
                return completion_handler( shared_from_this( ), response, status );
            } );
        }
        
        void Session::yield( const string data, const function< error_code ( const shared_ptr< Session >, const error_code ) > completion_handler )
        {
            if ( completion_handler == nullptr ) return;
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
            // adaptor->consume( [ this, completion_handler ]( auto adaptor, auto data, auto status ) {
            //     auto frame = frame_builder->assemble( data );
            //     //if finalised ... else consume.
            //     completion_handler( shared_from_this( ), response, status );
            // } );
        }
        
        void Session::fetch( const string delimiter, const function< error_code ( const shared_ptr< Session >, const Bytes, const error_code ) > completion_handler )
        {
            if ( completion_handler == nullptr ) return;
        }
        
        void Session::observe( const shared_ptr< Request > request, const function< milliseconds ( const shared_ptr< const Response > ) > event_handler, const function< error_code ( const shared_ptr< Session >, const shared_ptr< const Response >, const error_code ) > reaction_handler )
        {
            //user has to reschedule itself.
        }
        
        multimap< string, string > Session::get_default_headers( void ) const
        {
            multimap< string, string > values = m_pimpl->default_headers;
            
            for ( const auto& header : m_pimpl->computed_headers )
                values.emplace( header.first, header.second( ) );
                
            return values;
        }
        
        function< error_code ( const int, const string ) > Session::get_log_handler( void ) const
        {
            return m_pimpl->log_handler;
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
        
        void Session::set_log_handler( const function< error_code ( const int, const string ) >& value )
        {
            m_pimpl->log_handler = value;
        }
    }
}
