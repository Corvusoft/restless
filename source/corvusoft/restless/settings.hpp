/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <string>
#include <chrono>
#include <cstdint>

//Project Includes

//External Includes
#include <corvusoft/core/settings.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    
    namespace restless
    {
        //Forward Declarations
        
        class Settings : public core::Settings
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                Settings( void );
                
                virtual ~Settings( void );
                
                //Functionality
                
                //Getters
                std::uint16_t get_port( void ) const;
                
                std::string get_address( void ) const;
                
                std::string get_bind_address( void ) const;
                
                std::chrono::milliseconds get_connection_timeout( void ) const;
                
                //Setters
                void set_port( const std::uint16_t value );
                
                void set_address( const std::string& value );
                
                void set_bind_address( const std::string& value );
                
                void set_connection_timeout( const std::chrono::milliseconds& value );
                
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
                
                //Setters
                
                //Operators
                Settings& operator =( const Settings& value ) = delete;
                
                //Properties
        };
    }
}
