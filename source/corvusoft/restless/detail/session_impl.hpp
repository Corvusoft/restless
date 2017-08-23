/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTLESS_DETAIL_SESSION_IMPL_H
#define _CORVUSOFT_RESTLESS_DETAIL_SESSION_IMPL_H 1

//System Includes
#include <map>
#include <mutex>
#include <tuple>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <system_error>
#include <condition_variable>

//Project Includes

//External Includes

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
                std::mutex task_lock { };
                
                std::condition_variable pending_work { };
                
                std::shared_ptr< Settings > settings = nullptr;
                
                std::shared_ptr< core::RunLoop > runloop = nullptr;
                
                std::shared_ptr< network::Adaptor > network = nullptr;
                
                std::shared_ptr< protocol::Protocol > protocol = nullptr;
                
                std::vector< std::shared_ptr< network::Adaptor > > sockets { };
                
                std::multimap< std::string, std::string > default_headers { };
                
                std::multimap< std::string, const std::function< std::string ( void ) > > computed_headers { };
                
                std::function< std::error_code ( const int, const std::string ) > log_handler = nullptr;
                
                std::function< std::error_code ( const std::shared_ptr< const Request > ) > connection_timeout_handler = nullptr;
                
                std::function< std::error_code ( const std::shared_ptr< const Request >, const std::shared_ptr< const Response >, const std::error_code ) > error_handler = nullptr;
                
                std::vector< std::tuple< const std::shared_ptr< Request >,
                    const std::function< std::error_code ( const std::shared_ptr< const Response > ) >,
                    const std::function< std::error_code ( const std::shared_ptr< Request >, const std::shared_ptr< network::Adaptor > ) >,
                    const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > > > tasks { };
                    
                const std::function< void ( const std::shared_ptr< network::Adaptor > ) > open_handler = [ ]( const auto adaptor )
                {
                
                };
                
                const std::function< void ( const std::shared_ptr< network::Adaptor > ) > close_handler = [ ]( const auto adaptor )
                {
                
                };
                
                const std::function< void ( const std::shared_ptr< network::Adaptor > ) > message_handler = [ ]( const auto adaptor )
                {
                
                };
                
                const std::function< void ( const std::shared_ptr< network::Adaptor >, const std::error_code ) > fault_handler = [ ]( const auto adaptor, const auto error )
                {
                
                };
                
                std::error_code has_pending_requests( void ) const
                {
                    if ( task_lock.try_lock( ) == false ) return std::error_code( ); //shoudl be try again.
                    if ( tasks.empty( ) )
                    {
                        task_lock.unlock( );
                        return std::error_code( ); //should be no work aailabel.
                    }
                    
                    return std::error_code( );
                }
                
                std::error_code perform_request( const std::shared_ptr< network::Adaptor > adaptor )
                {
                    std::vector< std::tuple > requests { };
                    if ( settings->has_pipelining_enabled( ) ) requests = tasks;
                    else requests.emplace_back( tasks.front( ) ); //and remove.
                    
                    task_lock.unlock( );
                    pending_work.notify_one( );
                    
                    for ( auto request : requests )
                    {
                        //send request
                    }
                    
                    return std::error_code( );
                }
            };
        }
        
        std::error_code make_adaptor( std::shared_ptr< network::Adaptor >& adaptor ) //factory!
        {
            //auto adaptor = m_pimpl->network::create( );
            return std::error_code( );
        }
    }
}

#endif  /* _CORVUSOFT_RESTLESS_DETAIL_SESSION_IMPL_H */
