/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
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
        
        class Session : public std::enable_shared_from_this< Session >
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                Session( void );
                
                Session( const std::shared_ptr< network::Adaptor > adaptor, const std::shared_ptr< core::RunLoop > runloop );
                
                virtual ~Session( void );
                
                //Functionality
                void close( const std::function< std::error_code ( const std::shared_ptr< Session >, const std::error_code ) > completion_handler );
                
                void open( const std::shared_ptr< Settings > settings,
                           const std::function< std::error_code ( const std::shared_ptr< Session >, const std::error_code ) > completion_handler );
                           
                void open( const std::string& address,
                           const std::uint16_t port,
                           const std::function< std::error_code ( const std::shared_ptr< Session >, const std::error_code ) > completion_handler );
                           
                void send( const std::shared_ptr< Request > request,
                           const std::function< std::error_code ( const std::shared_ptr< Session >, const std::shared_ptr< const Response >, const std::error_code ) > completion_handler );
                           
                void yield( const std::string data,
                            const std::function< std::error_code ( const std::shared_ptr< Session >, const std::error_code ) > completion_handler );
                            
                void yield( const core::Bytes data,
                            const std::function< std::error_code ( const std::shared_ptr< Session >, const std::error_code ) > completion_handler );
                            
                void fetch( const std::size_t length,
                            const std::function< std::error_code ( const std::shared_ptr< Session >, const core::Bytes, const std::error_code ) > completion_handler );
                            
                void fetch( const std::string delimiter,
                            const std::function< std::error_code ( const std::shared_ptr< Session >, const core::Bytes, const std::error_code ) > completion_handler );
                            
                void observe( const std::shared_ptr< Request > request,
                              const std::function< std::chrono::milliseconds ( const std::shared_ptr< const Response > ) > event_handler,
                              const std::function< std::error_code ( const std::shared_ptr< Session >, const std::shared_ptr< const Response >, const std::error_code ) > reaction_handler );
                              
                //Getters
                std::shared_ptr< Settings > get_settings( void ) const;
                
                std::multimap< std::string, std::string > get_default_headers( void ) const;
                
                //Setters
                void set_default_header( const std::string& name, const std::string& value );
                
                void set_default_header( const std::string& name, const std::function< std::string ( void ) >& value );
                
                void set_default_headers( const std::multimap< std::string, std::string >& values );
                
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
