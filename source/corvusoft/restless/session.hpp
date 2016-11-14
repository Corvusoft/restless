/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTLESS_SETTINGS_H
#define _RESTLESS_SETTINGS_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <cstddef>
#include <functional>

//Project Includes
#include <corvusoft/restless/uri.hpp>
#include <corvusoft/restless/byte.hpp>
#include <corvusoft/restless/request.hpp>
#include <corvusoft/restless/response.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restless
{
    //Forward Declarations
    class Settings;
    
    namespace detail
    {
        class SessionImpl;
    }
    
    class Session
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Session( void );
            
            Session( const std::shared_ptr< const Settings >& settings );
            
            virtual ~Session( void );
            
            //Functionality
            void close( void );
            
            bool is_open( void ) const;
            
            bool is_closed( void ) const;
            
            void yield( const Bytes& body );
            
            void yield( const std::string& body );
            
            void yield( const Bytes& body, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
            void yield( const std::string& body, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
            void fetch( const std::size_t length );
            
            void fetch( const std::string& delimiter );
            
            void fetch( const std::size_t length, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
            void fetch( const std::string& delimiter, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
            const std::shared_ptr< Response > send( const std::shared_ptr< Request >& request, const std::function< void ( const std::shared_ptr< Session > ) >& response_handler = nullptr );
            
            const std::shared_ptr< Response > send( const std::shared_ptr< Request >& request, const std::function< void ( const std::shared_ptr< Session > ) >& upload_handler, const std::function< void ( const std::shared_ptr< Session > ) >& response_handler );
            
            void wait( const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            //Getters
            const std::shared_ptr< Request > get_request( void ) const;
            
            const std::shared_ptr< Response > get_response( void ) const;
            
            const std::multimap< std::string, std::string > get_headers( void ) const;
            
            //Setters
            void add_header( const std::string& name, const std::string& value );
            
            void set_header( const std::string& name, const std::string& value );
            
            void set_headers( const std::multimap< std::string, std::string >& values );
            
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

#endif  /* _RESTLESS_SETTINGS_H */
