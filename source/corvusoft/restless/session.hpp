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
#include <corvusoft/core/byte.hpp>

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
                
                std::error_code close( const std::function< std::error_code ( const std::shared_ptr< Session >, const std::error_code error ) > completion_handler );
                
                std::error_code open( const std::string& address,
                                      const uint16_t port,
                                      const std::function< std::error_code ( const std::shared_ptr< Session >, const std::error_code error ) > completion_handler );
                                      
                std::error_code send( const std::shared_ptr< Request > request,
                                      const std::function< std::error_code ( const std::shared_ptr< Session >, const std::shared_ptr< const Response >, const std::error_code error ) > completion_handler );
                                      
                std::error_code yield( const std::string data,
                                       const std::function< std::error_code ( const std::shared_ptr< Session >, const std::error_code error ) > completion_handler );
                                       
                std::error_code yield( const core::Bytes data,
                                       const std::function< std::error_code ( const std::shared_ptr< Session >, const std::error_code error ) > completion_handler );
                                       
                std::error_code fetch( const std::size_t length,
                                       const std::function< std::error_code ( const std::shared_ptr< Session >, const core::Bytes, const std::error_code error ) > completion_handler );
                                       
                std::error_code fetch( const std::string delimiter,
                                       const std::function< std::error_code ( const std::shared_ptr< Session >, const core::Bytes, const std::error_code error ) > completion_handler );
                                       
                std::error_code observe( const std::shared_ptr< Request > request,
                                         const std::function< std::chrono::milliseconds ( const std::shared_ptr< const Response > ) > event_handler,
                                         const std::function< std::error_code ( const std::shared_ptr< Session >, const std::shared_ptr< const Response >, const std::error_code error ) > reaction_handler );
                //Getters
                std::shared_ptr< Settings > get_settings( void ) const;
                
                std::shared_ptr< core::RunLoop > get_runloop( void ) const;
                
                std::shared_ptr< network::Adaptor > get_adaptor( void ) const;
                
                std::shared_ptr< protocol::Protocol > get_protocol( void ) const;
                
                std::multimap< std::string, std::string > get_default_headers( void ) const;
                
                std::function< std::error_code ( const int, const std::string ) > get_log_handler( void ) const;
                
                std::function< std::error_code ( const std::shared_ptr< const Request > ) > get_connection_timeout_handler( void ) const;
                
                std::function< std::error_code ( const std::shared_ptr< const Request >, const std::shared_ptr< const Response >, const std::error_code ) > get_error_handler( void ) const;
                
                //Setters
                //void set_data
                
                void set_settings( const std::shared_ptr< Settings >& value );
                
                void set_runloop( const std::shared_ptr< core::RunLoop >& value );
                
                void set_adaptor( const std::shared_ptr< network::Adaptor >& value );
                
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
