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
            Session( const Uri& uri, const std::shared_ptr< const Settings >& settings = nullptr );
            
            virtual ~Session( void );
            
            //Functionality
            void wait( void );
            
            void close( void );
            
            bool is_open( void ) const;
            
            bool is_closed( void ) const;
            
            Bytes fetch( const std::size_t length, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            Bytes fetch( const std::string& delimiter, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            const std::shared_ptr< Response > send( const std::shared_ptr< Request >& request, const std::function< void ( const std::shared_ptr< Session > ) >& response_handler = nullptr );
            
            const std::shared_ptr< Response > send( const std::shared_ptr< Request >& request, const std::function< std::size_t ( const std::shared_ptr< Session > ) >& upload_handler, const std::function< void ( const std::shared_ptr< Session > ) >& response_handler = nullptr );
            
            //Getters
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
            Session( void ) = delete;
            
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
