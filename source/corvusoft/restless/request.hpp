/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <string>
#include <memory>

//Project Includes

//External Includes
#include <corvusoft/core/byte.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    
    namespace restless
    {
        //Forward Declarations
        namespace detail
        {
            struct RequestImpl;
        }
        
        class Request final
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                Request( void );
                
                virtual ~Request( void );
                
                //Functionality
                
                //Getters
                double get_version( void ) const;
                
                core::Bytes get_body( void ) const;
                
                std::string get_path( void ) const;
                
                std::string get_method( void ) const;
                
                std::string get_protocol( void ) const;
                
                std::string get_header( const std::string& name ) const;
                
                std::multimap< std::string, std::string > get_headers( void ) const;
                
                std::string get_query_parameter( const std::string& name ) const;
                
                std::multimap< std::string, std::string > get_query_parameters( void ) const;
                
                //Setters
                void set_version( const double value );
                
                void set_body( const core::Bytes& value );
                
                void set_body( const std::string& value );
                
                void set_path( const std::string& value );
                
                void set_method( const std::string& value );
                
                void set_protocol( const std::string& value );
                
                void set_header( const std::string& name, const std::string& value );
                
                void set_headers( const std::multimap< std::string, std::string >& values );
                
                void set_query_parameter( const std::string& name, const std::string& value );
                
                void set_query_parameters( const std::multimap< std::string, std::string >& values );
                
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
                Request( const Request& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Request& operator =( const Request& value ) = delete;
                
                //Properties
                std::unique_ptr< detail::RequestImpl > m_pimpl;
        };
    }
}
