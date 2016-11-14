/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTLESS_SETTINGS_H
#define _RESTLESS_SETTINGS_H 1

//System Includes
#include <map>
#include <string>
#include <cstddef>

//Project Includes

//External Includes
#include <corvusoft/restbed/settings.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restless
{
    //Forward Declarations
    
    class Settings : public restbed::Settings
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Settings( void );
            
            virtual ~Settings( void );
            
            //Functionality
            
            //Getters
            
            //Setters
            
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
            Settings( const Settings& original ) = delete;
            
            //Functionality
            
            //Getters
            uint16_t get_port( void ) const = delete;
            
            std::string get_root( void ) const = delete;
            
            bool get_case_insensitive_uris( void ) const = delete;
            
            unsigned int get_connection_limit( void ) const = delete;
            
            std::string get_status_message( const int code ) const = delete;
            
            std::map< int, std::string > get_status_messages( void ) const = delete;
            
            //Setters
            void set_port( const uint16_t value ) = delete;
            
            void set_root( const std::string& value ) = delete;
            
            void set_case_insensitive_uris( const bool value ) = delete;
            
            void set_connection_limit( const unsigned int value ) = delete;
            
            void set_status_message( const int code, const std::string& message ) = delete;
            
            void set_status_messages( const std::map< int, std::string >& values ) = delete;
            
            //Operators
            Settings& operator =( const Settings& value ) = delete;
            
            //Properties
    };
}

#endif  /* _RESTLESS_SETTINGS_H */
