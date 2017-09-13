/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTLESS_DETAIL_SESSION_IMPL_H
#define _CORVUSOFT_RESTLESS_DETAIL_SESSION_IMPL_H 1

//System Includes
#include <map>
#include <tuple>
#include <stack>
#include <memory>
#include <string>
#include <functional>
#include <system_error>

//Project Includes

//External Includes
#include <corvusoft/protocol/protocol.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    namespace core
    {
        class RunLoop;
    }
    
    namespace network
    {
        class Adaptor;
    }
    
    namespace protocol
    {
        class Protocol;
    }
    
    namespace restless
    {
        //Forward Declarations
        class Settings;
        
        namespace detail
        {
            //Forward Declarations
            
            struct SessionImpl
            {
                std::shared_ptr< Settings > settings = nullptr;
                
                std::shared_ptr< core::RunLoop > runloop = nullptr;
                
                std::shared_ptr< network::Adaptor > adaptor = nullptr;
                
                std::shared_ptr< protocol::Protocol > protocol = nullptr;
                
                std::multimap< std::string, std::string > default_headers { };
                
                std::multimap< std::string, const std::function< std::string ( void ) > > computed_headers { };
                
                std::function< std::error_code ( const int, const std::string ) > log_handler = nullptr;
                
                std::function< std::error_code ( const std::shared_ptr< const Request > ) > connection_timeout_handler = nullptr;
                
                std::function< std::error_code ( const std::shared_ptr< const Request >, const std::shared_ptr< const Response >, const std::error_code ) > error_handler = nullptr;
                
                std::stack< std::tuple< const std::shared_ptr< Request >,
                    const std::function< std::error_code ( const std::shared_ptr< const Response > ) >,
                    const std::function< std::error_code ( const std::shared_ptr< Request >, const std::shared_ptr< network::Adaptor > ) >,
                    const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > > > tasks { };
                    
                const std::function< void ( const std::shared_ptr< network::Adaptor > ) > open_handler = [ ]( const auto adaptor )
                {
                
                };
                
                const std::function< void ( const std::shared_ptr< network::Adaptor > ) > close_handler = [ ]( const auto adaptor )
                {
                    //runloop->cancel( "adaptor key" );
                };
                
                const std::function< void ( const std::shared_ptr< network::Adaptor > ) > message_handler = [ ]( const auto adaptor )
                {
                
                };
                
                const std::function< void ( const std::shared_ptr< network::Adaptor >, const std::error_code ) > fault_handler = [ ]( const auto adaptor, const auto error )
                {
                    //log error then
                    //if error code == connection timeout: connection_timeout_handler( );
                    //else fault_handler( );
                };
                
                const std::function< std::error_code ( void ) > has_pending_requests = [ this ]( void )
                {
                    if ( not tasks.empty( ) )
                        return std::error_code( );
                        
                    return std::make_error_code( std::errc::operation_not_permitted );
                };
                
                const std::function< std::error_code ( void ) > perform_request = [ this ]( void )
                {
                    while ( not tasks.empty( ) )
                    {
                        const auto task = tasks.top( );
                        const auto request = std::get< 0 >( task );
                        const auto response_handler = std::get< 1 >( task );
                        const auto upload_handler = std::get< 2 >( task );
                        const auto download_handler = std::get< 3 >( task );
                        
                        auto error = protocol->compose( adaptor, request ); //check for null on adaptor and protocol etc...
                        //if ( error )
                        
                        tasks.pop( );
                    }
                    
                    //adaptor->set_message_handler( bind( m_pimpl->message_handler, response_handler ) );//std::bind
                    
                    //add headers
                    //std::error_code status { };
                    //status = protocol->compose( request, adaptor );
                    //if ( status ) return status; //call error handler and/or log.
                    
                    //for upload handler.
                    
                    return std::error_code( ); //reschedule response code.
                };
            };
        }
    }
}

#endif  /* _CORVUSOFT_RESTLESS_DETAIL_SESSION_IMPL_H */
