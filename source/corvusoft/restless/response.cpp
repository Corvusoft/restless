/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <stdexcept>

//Project Includes
#include "corvusoft/restless/status.hpp"
#include "corvusoft/restless/response.hpp"

//External Includes

//System Namespaces
using std::stod;
using std::string;
using std::function;
using std::multimap;
using std::out_of_range;
using std::invalid_argument;

//Project Namespaces

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;
using corvusoft::core::make_string;
using corvusoft::protocol::Message;

namespace corvusoft
{
    namespace restless
    {
        Response::Response( void ) : Message( )
        {
            return;
        }
        
        Response::~Response( void )
        {
            return;
        }
        
        bool Response::has_header( const string& name ) const
        {
            return has( "header:" + name );
        }
        
        double Response::get_version( void ) const
        {
            static const auto default_value = 0.0;
            if ( not has( "version" ) ) return default_value;
            
            try
            {
                return stod( make_string( get( "version" ) ) );
            }
            catch ( const out_of_range& oor   )
            {
                return default_value;
            }
            catch ( const invalid_argument ia )
            {
                return default_value;
            }
            return default_value;
        }
        
        int Response::get_status_code( void ) const
        {
            static const auto default_value = 0;
            if ( not has( "status:code" ) ) return default_value;
            
            try
            {
                return stod( make_string( get( "status:code" ) ) );
            }
            catch ( const out_of_range& oor   )
            {
                return default_value;
            }
            catch ( const invalid_argument ia )
            {
                return default_value;
            }
            return default_value;
        }
        
        string Response::get_status_message( const function< string ( const string& ) >& transform ) const
        {
            return "";
        }
        
        string Response::get_protocol( const function< string ( const string& ) >& transform ) const
        {
        
        }
        
        Bytes Response::get_body( const function< string ( const Bytes& ) >& transform ) const
        {
        
        }
        
        string Response::get_header( const string& name, const string& default_value ) const
        {
        
        }
        
        string Response::get_header( const string& name, const function< string ( const string& ) >& transform ) const
        {
        
        }
        
        multimap< string, string > Response::get_headers( const string& name ) const
        {
        
        }
        
        void Response::set_version( const double value )
        {
            //set( "version", value );
        }
        
        void Response::set_status_code( const int value )
        {
            //set( "status:code", value );
            //set_status_message( make_status_message( value ) );
        }
        
        void Response::set_status_message( const string& value )
        {
            //set( "status:message", value );
        }
        
        void Response::set_protocol( const string& value )
        {
            //set( "protocol", value );
        }
        
        void Response::set_body( const string& value )
        {
            //set( "body", make_bytes( value ) );
        }
        
        void Response::set_body( const Bytes& value )
        {
            //set( "body", value );
        }
        
        void Response::set_header( const string& name, const string& value )
        {
            //erase( "header:" + name );
            //add_header( name, value );
        }
        
        void Response::set_headers( const multimap< string, string >& values )
        {
            //erase( "header:" + name );
            //add_header( name, value );
        }
    }
}
