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
        
        void Session::close( void )
        {
        
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
        
        void Session::wait( const milliseconds& duration )
        {
            if ( m_pimpl->runloop )
                m_pimpl->runloop->wait( duration );
        }
        
        void Session::get( const shared_ptr< Request > request,
                           const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                           const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                           const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "GET" );
            send( request, response_handler, upload_handler, download_handler );
        }
        
        void Session::get( const shared_ptr< Request > request,
                           const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                           const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "GET" );
            send( request, response_handler, download_handler );
        }
        
        void Session::put( const shared_ptr< Request > request,
                           const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                           const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                           const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "PUT" );
            send( request, response_handler, upload_handler, download_handler );
        }
        
        void Session::put( const shared_ptr< Request > request,
                           const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                           const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "PUT" );
            send( request, response_handler, download_handler );
        }
        
        void Session::post( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "POST" );
            send( request, response_handler, upload_handler, download_handler );
        }
        
        void Session::post( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "POST" );
            send( request, response_handler, download_handler );
        }
        
        void Session::patch( const shared_ptr< Request > request,
                             const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                             const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                             const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "PATCH" );
            send( request, response_handler, upload_handler, download_handler );
        }
        
        void Session::patch( const shared_ptr< Request > request,
                             const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                             const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "PATCH" );
            send( request, response_handler, download_handler );
        }
        
        void Session::head( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "HEAD" );
            send( request, response_handler, upload_handler, download_handler );
        }
        
        void Session::head( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "HEAD" );
            send( request, response_handler, download_handler );
        }
        
        void Session::destroy( const shared_ptr< Request > request,
                               const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                               const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                               const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "DELETE" );
            send( request, response_handler, upload_handler, download_handler );
        }
        
        void Session::destroy( const shared_ptr< Request > request,
                               const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                               const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "DELETE" );
            send( request, response_handler, download_handler );
        }
        
        void Session::options( const shared_ptr< Request > request,
                               const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                               const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                               const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "OPTIONS" );
            send( request, response_handler, upload_handler, download_handler );
        }
        
        void Session::options( const shared_ptr< Request > request,
                               const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                               const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "OPTIONS" );
            send( request, response_handler, download_handler );
        }
        
        void Session::trace( const shared_ptr< Request > request,
                             const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                             const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                             const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "TRACE" );
            send( request, response_handler, upload_handler, download_handler );
        }
        
        void Session::trace( const shared_ptr< Request > request,
                             const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                             const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            request->set_method( "TRACE" );
            send( request, response_handler, download_handler );
        }
        
        void Session::send( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
        
        }
        
        void Session::send( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {
            send( request, response_handler, nullptr, download_handler );
        }
        
        void Session::observe( const shared_ptr< Request > request,
                               const function< milliseconds ( const shared_ptr< const Response > ) > event_handler,
                               const function< error_code ( const shared_ptr< const Response > ) > reaction_handler )
        {
            //to reschedule itself.
        }
        
        string Session::get_key( void ) const
        {
            return m_pimpl->key;
        }
        
        shared_ptr< Settings > Session::get_settings( void ) const
        {
            return m_pimpl->settings;
        }
        
        shared_ptr< RunLoop > Session::get_runloop( void ) const
        {
            return m_pimpl->runloop;
        }
        
        shared_ptr< Adaptor > Session::get_network( void ) const
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
        
        void Session::set_key( const string& value )
        {
            m_pimpl->key = value;
        }
        
        void Session::set_settings( const shared_ptr< Settings >& value )
        {
            m_pimpl->settings = value;
        }
        
        void Session::set_runloop( const shared_ptr< RunLoop >& value )
        {
            m_pimpl->runloop = value;
        }
        
        void Session::set_network( const shared_ptr< Adaptor >& value )
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
