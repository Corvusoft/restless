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
#include "corvusoft/restless/log_level.hpp"
#include "corvusoft/restless/detail/session_impl.hpp"

//External Includes
#include <corvusoft/core/run_loop.hpp>
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
        }
        
        bool Session::is_closed( void ) const
        {

        }

        void Session::wait( const milliseconds& duration )
        {

        }

        void Session::get( const shared_ptr< Request > request,
                        const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                        const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                        const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }
        
        void Session::get( const shared_ptr< Request > request,
                        const function< void ( const shared_ptr< const Response > ) > response_handler,
                        const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }

        void Session::put( const shared_ptr< Request > request,
                        const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                        const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                        const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }
        
        void Session::put( const shared_ptr< Request > request,
                        const function< void ( const shared_ptr< const Response > ) > response_handler,
                        const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }

        void Session::post( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }
        
        void Session::post( const shared_ptr< Request > request,
                            const function< void ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }

        void Session::patch( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }
        
        void Session::patch( const shared_ptr< Request > request,
                            const function< void ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }

        void Session::head( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }
        
        void Session::head( const shared_ptr< Request > request,
                            const function< void ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }

        void Session::destroy( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }
        
        void Session::destroy( const shared_ptr< Request > request,
                            const function< void ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }

        void Session::options( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }
        
        void Session::options( const shared_ptr< Request > request,
                            const function< void ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }

        void Session::trace( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }
        
        void Session::trace( const shared_ptr< Request > request,
                            const function< void ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }

        void Session::send( const shared_ptr< Request > request,
                            const function< error_code ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }
        
        void Session::send( const shared_ptr< Request > request,
                            const function< void ( const shared_ptr< const Response > ) > response_handler,
                            const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
        {

        }

        void Session::observe( const shared_ptr< Request > request,
                            const function< milliseconds ( const shared_ptr< const Response > ) > event_handler,
                            const function< error_code ( const shared_ptr< const Response > ) > reaction_handler )
        {
            //to reschedule itself.
        }

        string Session::get_key( void ) const
        {

        }

        shared_ptr< Settings > Session::get_settings( void ) const
        {

        }

        shared_ptr< RunLoop > Session::get_runloop( void ) const
        {

        }

        shared_ptr< Adaptor > Session::get_network( void ) const
        {

        }

        shared_ptr< Protocol > Session::get_protocol( void ) const
        {

        }

        multimap< const string, const string > Session::get_default_headers( void ) const
        {

        }

        function< error_code ( const int, const string ) > Session::get_log_handler( void ) const
        {

        }

        function< error_code ( const shared_ptr< const Request > ) > Session::get_connection_timeout_handler( void ) const
        {

        }

        function< error_code ( const shared_ptr< const Request >, const shared_ptr< const Response >, const error_code ) > Session::get_error_handler( void ) const
        {

        }
        
        void Session::set_key( const string& value )
        {

        }

        void Session::set_settings( const shared_ptr< Settings >& value )
        {

        }

        void Session::set_runloop( const shared_ptr< RunLoop >& value )
        {

        }

        void Session::set_network( const shared_ptr< Adaptor >& value )
        {

        }

        void Session::set_protocol( const shared_ptr< Protocol >& value )
        {

        }

        void Session::set_default_header( const string& name, const string& value )
        {

        }
        
        void Session::set_default_header( const string& name, const function< string ( void ) >& value )
        {

        }

        void Session::set_deafult_headers( const multimap< const string, const string >& values )
        {

        }
        
        void Session::set_log_handler( const function< error_code ( const int, const string ) >& value )
        {

        }
        
        void Session::set_connection_timeout_handler( const function< error_code ( const shared_ptr< const Request > ) >& value )
        {

        }

        void Session::set_error_handler( const function< error_code ( const shared_ptr< const Request >, const shared_ptr< const Response >, const error_code ) >& value )
        {

        }
    }
}
