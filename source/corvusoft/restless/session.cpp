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
#include <corvusoft/core/run_loop.hpp>
#include <corvusoft/core/log_level.hpp>
#include <corvusoft/protocol/http.hpp>
#include <corvusoft/protocol/protocol.hpp>
#include <corvusoft/network/adaptor.hpp>
#include <corvusoft/network/tcpip_adaptor.hpp> //why not just call it tcpip.hpp?

//System Namespaces
using std::string;
using std::function;
using std::multimap;
using std::error_code;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_error_code;
using std::chrono::milliseconds;

//Project Namespaces
using corvusoft::restless::detail::SessionImpl;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::RunLoop;
using corvusoft::protocol::HTTP;
using corvusoft::protocol::Protocol;
using corvusoft::network::Adaptor;
using corvusoft::network::TCPIPAdaptor; //rename TCPIP

namespace corvusoft
{
    namespace restless
    {
        Session::Session( void ) : m_pimpl( new SessionImpl )
        {
            return;
        }
        
        Session::~Session( void )
        {
            return;
        }
        
        bool Session::is_open( void ) const
        {
            //has pending requests
            return false;
        }
        
        bool Session::is_closed( void ) const
        {
            return true;
        }
        
        error_code Session::close( const function< error_code ( const shared_ptr< Session >, const error_code error ) > completion_handler )
        {
            return error_code( );
        }
        
        error_code Session::open( const string& address, const uint16_t port, const function< error_code ( const shared_ptr< Session >, const error_code error ) > completion_handler )
        {
            if ( not m_pimpl->runloop  ) m_pimpl->runloop = make_shared< RunLoop >( );
            if ( not m_pimpl->adaptor  ) m_pimpl->adaptor = TCPIPAdaptor::create( ); //remove the creat method it can't be force across implementations.
            if ( not m_pimpl->protocol ) m_pimpl->protocol = make_shared< HTTP >( );
            if ( not m_pimpl->settings ) m_pimpl->settings = make_shared< Settings >( );
            
            const auto settings = make_shared< Settings >( ); //why not just m_pimpl->settings?
            settings->set( "port", port );
            settings->set( "address", address ); //provide Hostname::to_address( hostname ); functionality in network. i.e this might be /dev/sda0
            
            //m_pimpl->protocol->setup( ); //don't forget teardown.
            
            auto error = m_pimpl->adaptor->setup( m_pimpl->runloop );
            if ( error ) return error;
            
            error = m_pimpl->adaptor->open( settings );
            if ( error ) return error;
            
            return error_code( ); //m_pimpl->runloop->start( );
            //we need to review the adaptor API, if you must call runloop->start
            //then it should a mandatory DI element.
        }
        
        error_code Session::send( const shared_ptr< Request > request,
                                  const function< error_code ( const shared_ptr< Session >, const shared_ptr< const Response > response, const error_code error ) > completion_handler )
        {
            //return ( error ) ? m_pimpl->error_handler( ) : error_code( );
            return error_code( );
        }
        
        error_code yield( const string data,
                          const function< error_code ( const shared_ptr< Session >, const error_code error ) > completion_handler )
        {
            return error_code( );
        }
        
        error_code yield( const Bytes data,
                          const function< error_code ( const shared_ptr< Session >, const error_code error ) > completion_handler )
        {
            return error_code( );
        }
        
        error_code fetch( const size_t length,
                          const function< error_code ( const shared_ptr< Session >, const Bytes, const error_code error ) > completion_handler )
        {
            return error_code( );
        }
        
        error_code fetch( const string delimiter,
                          const function< error_code ( const shared_ptr< Session >, const Bytes, const error_code error ) > completion_handler )
        {
            return error_code( );
        }
        
        error_code Session::observe( const shared_ptr< Request > request,
                                     const function< milliseconds ( const shared_ptr< const Response > ) > event_handler,
                                     const function< error_code ( const shared_ptr< Session >, const shared_ptr< const Response > response, const error_code error ) > reaction_handler )
        {
            //user has to reschedule itself.
            return error_code( );
        }
        
        shared_ptr< Settings > Session::get_settings( void ) const
        {
            return m_pimpl->settings;
        }
        
        shared_ptr< RunLoop > Session::get_runloop( void ) const
        {
            return m_pimpl->runloop;
        }
        
        shared_ptr< Adaptor > Session::get_adaptor( void ) const
        {
            return m_pimpl->adaptor;
        }
        
        shared_ptr< Protocol > Session::get_protocol( void ) const
        {
            return m_pimpl->protocol;
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
        
        function< error_code ( const shared_ptr< const Request > ) > Session::get_connection_timeout_handler( void ) const
        {
            return m_pimpl->connection_timeout_handler;
        }
        
        function< error_code ( const shared_ptr< const Request >, const shared_ptr< const Response >, const error_code ) > Session::get_error_handler( void ) const
        {
            return m_pimpl->error_handler;
        }
        
        void Session::set_settings( const shared_ptr< Settings >& value )
        {
            m_pimpl->settings = value;
        }
        
        void Session::set_runloop( const shared_ptr< RunLoop >& value )
        {
            m_pimpl->runloop = value;
        }
        
        void Session::set_adaptor( const shared_ptr< Adaptor >& value )
        {
            m_pimpl->adaptor = value;
        }
        
        void Session::set_protocol( const shared_ptr< Protocol >& value )
        {
            m_pimpl->protocol = value;
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
        
        void Session::set_connection_timeout_handler( const function< error_code ( const shared_ptr< const Request > ) >& value )
        {
            m_pimpl->connection_timeout_handler = value;
        }
        
        void Session::set_error_handler( const function< error_code ( const shared_ptr< const Request >, const shared_ptr< const Response >, const error_code ) >& value )
        {
            m_pimpl->error_handler = value;
        }
    }
}
