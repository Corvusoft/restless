/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTLESS_RESPONSE_H
#define _CORVUSOFT_RESTLESS_RESPONSE_H 1

//System Includes
#include <map>
#include <string>
#include <functional>
#include <type_traits>

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
        
        class Response final : public protocol::Message
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                Response( void );
                
                virtual ~Response( void );
                
                //Functionality
                bool has_header( const std::string& name ) const;
                
                //Getters
                double get_version( void ) const;

                int get_status_code( void ) const;

                std::string get_status_message( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;                
                
                std::string get_protocol( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
                
                core::Bytes get_body( const std::function< std::string ( const core::Bytes& ) >& transform = nullptr ) const;

                template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
                Type get_header( const std::string& name, const Type default_value ) const
                {
                    return default_value;
                }
                
                std::string get_header( const std::string& name, const std::string& default_value ) const;
                
                std::string get_header( const std::string& name, const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
                
                std::multimap< std::string, std::string > get_headers( const std::string& name = "" ) const;
                
                //Setters
                void set_version( const double value );
                
                void set_status_code( const int value );
                
                void set_status_message( const std::string& value );
                
                void set_protocol( const std::string& protocol );
                
                void set_body( const std::string& value );
                
                void set_body( const core::Bytes& value );
                
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
                Response( const Response& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Response& operator =( const Response& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _CORVUSOFT_RESTLESS_RESPONSE_H */
