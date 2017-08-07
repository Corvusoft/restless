/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTLESS_REQUEST_H
#define _CORVUSOFT_RESTLESS_REQUEST_H 1

//System Includes
#include <map>
#include <string>

//Project Includes

//External Includes
#include <corvusoft/core/byte.hpp>
#include <corvusoft/protocol/message.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    
    namespace restless
    {
        //Forward Declarations
        
        class Request final : public protocol::Message
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                Request( void );
                
                virtual ~Request( void );
                
                //Functionality
                
                //Getters
                //core::URI get_uri( void ) const;
                
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
                //void set_uri( const core::URI& value );
                
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
        };
    }
}

#endif  /* _CORVUSOFT_RESTLESS_REQUEST_H */
