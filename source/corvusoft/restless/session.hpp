/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTLESS_SESSION_H
#define _CORVUSOFT_RESTLESS_SESSION_H 1

//System Includes
#include <map>
#include <chrono>
#include <string>
#include <memory>
#include <cstdint>
#include <functional>
#include <system_error>

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
        class Request;
        class Response;
        class Settings;
        
        namespace detail
        {
            struct SessionImpl;
        }
        
        class Session
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                Session( void );
                
                virtual ~Session( void );
                
                //Functionality
                bool is_open( void ) const;
                
                bool is_closed( void ) const;
                
                std::error_code close( void );
                
                std::error_code open( const std::string& full_qualified_domain_name, const uint16_t port = 80 );
                
                //std::error_code resume( void );
                
                //std::error_code suspend( void );
                
                std::error_code wait( const std::chrono::milliseconds& duration = std::chrono::milliseconds::min( ) );
                
                std::error_code get( const std::shared_ptr< Request > request,
                                     const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                     const std::function< std::error_code ( const std::shared_ptr< Request >, const std::shared_ptr< network::Adaptor > ) > upload_handler = nullptr,
                                     const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                     
                std::error_code get( const std::shared_ptr< Request > request,
                                     const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                     const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                     
                std::error_code put( const std::shared_ptr< Request > request,
                                     const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                     const std::function< std::error_code ( const std::shared_ptr< Request >, const std::shared_ptr< network::Adaptor > ) > upload_handler = nullptr,
                                     const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                     
                std::error_code put( const std::shared_ptr< Request > request,
                                     const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                     const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                     
                std::error_code post( const std::shared_ptr< Request > request,
                                      const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                      const std::function< std::error_code ( const std::shared_ptr< Request >, const std::shared_ptr< network::Adaptor > ) > upload_handler = nullptr,
                                      const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                      
                std::error_code post( const std::shared_ptr< Request > request,
                                      const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                      const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                      
                std::error_code patch( const std::shared_ptr< Request > request,
                                       const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                       const std::function< std::error_code ( const std::shared_ptr< Request >, const std::shared_ptr< network::Adaptor > ) > upload_handler = nullptr,
                                       const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                       
                std::error_code patch( const std::shared_ptr< Request > request,
                                       const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                       const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                       
                std::error_code head( const std::shared_ptr< Request > request,
                                      const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                      const std::function< std::error_code ( const std::shared_ptr< Request >, const std::shared_ptr< network::Adaptor > ) > upload_handler = nullptr,
                                      const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                      
                std::error_code head( const std::shared_ptr< Request > request,
                                      const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                      const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                      
                std::error_code destroy( const std::shared_ptr< Request > request,
                                         const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                         const std::function< std::error_code ( const std::shared_ptr< Request >, const std::shared_ptr< network::Adaptor > ) > upload_handler = nullptr,
                                         const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                         
                std::error_code destroy( const std::shared_ptr< Request > request,
                                         const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                         const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                         
                std::error_code options( const std::shared_ptr< Request > request,
                                         const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                         const std::function< std::error_code ( const std::shared_ptr< Request >, const std::shared_ptr< network::Adaptor > ) > upload_handler = nullptr,
                                         const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                         
                std::error_code options( const std::shared_ptr< Request > request,
                                         const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                         const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                         
                std::error_code trace( const std::shared_ptr< Request > request,
                                       const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                       const std::function< std::error_code ( const std::shared_ptr< Request >, const std::shared_ptr< network::Adaptor > ) > upload_handler = nullptr,
                                       const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                       
                std::error_code trace( const std::shared_ptr< Request > request,
                                       const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                       const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                       
                std::error_code send( const std::shared_ptr< Request > request,
                                      const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                      const std::function< std::error_code ( const std::shared_ptr< Request >, const std::shared_ptr< network::Adaptor > ) > upload_handler = nullptr,
                                      const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                      
                std::error_code send( const std::shared_ptr< Request > request,
                                      const std::function< std::error_code ( const std::shared_ptr< const Response > ) > response_handler,
                                      const std::function< std::error_code ( const std::shared_ptr< Response >, const std::shared_ptr< network::Adaptor > ) > download_handler = nullptr );
                                      
                std::error_code observe( const std::shared_ptr< Request > request,
                                         const std::function< std::chrono::milliseconds ( const std::shared_ptr< const Response > ) > event_handler,
                                         const std::function< std::error_code ( const std::shared_ptr< const Response > ) > reaction_handler );
                //Getters
                std::shared_ptr< Settings > get_settings( void ) const;
                
                std::shared_ptr< core::RunLoop > get_runloop( void ) const;
                
                std::shared_ptr< network::Adaptor > get_network( void ) const;
                
                std::shared_ptr< protocol::Protocol > get_protocol( void ) const;
                
                std::multimap< std::string, std::string > get_default_headers( void ) const;
                
                std::function< std::error_code ( const int, const std::string ) > get_log_handler( void ) const;
                
                std::function< std::error_code ( const std::shared_ptr< const Request > ) > get_connection_timeout_handler( void ) const;
                
                std::function< std::error_code ( const std::shared_ptr< const Request >, const std::shared_ptr< const Response >, const std::error_code ) > get_error_handler( void ) const;
                
                //Setters
                void set_settings( const std::shared_ptr< Settings >& value );
                
                void set_runloop( const std::shared_ptr< core::RunLoop >& value );
                
                void set_network( const std::shared_ptr< network::Adaptor >& value );
                
                void set_protocol( const std::shared_ptr< protocol::Protocol >& value );
                
                void set_default_header( const std::string& name, const std::string& value );
                
                void set_default_header( const std::string& name, const std::function< std::string ( void ) >& value );
                
                void set_default_headers( const std::multimap< std::string, std::string >& values );
                
                void set_log_handler( const std::function< std::error_code ( const int, const std::string ) >& value );
                
                void set_connection_timeout_handler( const std::function< std::error_code ( const std::shared_ptr< const Request > ) >& value );
                
                void set_error_handler( const std::function< std::error_code ( const std::shared_ptr< const Request >, const std::shared_ptr< const Response >, const std::error_code ) >& value );
                
                //Operators
                
                //Properties
                
            protected:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            private:
                //Friends
                
                //Definitions
                
                //Constructors
                Session( const Session& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Session& operator =( const Session& value ) = delete;
                
                //Properties
                std::unique_ptr< detail::SessionImpl > m_pimpl;
        };
    }
}

#endif  /* _CORVUSOFT_RESTLESS_SESSION_H */
