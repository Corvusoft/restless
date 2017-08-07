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
using std::stoi;
using std::stod;
using std::string;
using std::to_string;
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
            catch ( const out_of_range& )
            {
                return default_value;
            }
            catch ( const invalid_argument& )
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
                return stoi( make_string( get( "status:code" ) ) );
            }
            catch ( const out_of_range& )
            {
                return default_value;
            }
            catch ( const invalid_argument& )
            {
                return default_value;
            }
            
            return default_value;
        }
        
        string Response::get_status_message( const function< string ( const string& ) >& transform ) const
        {
            const auto value = make_string( get( "status:message" ) );
            return transform ? transform( value ) : value;
        }
        
        string Response::get_protocol( const function< string ( const string& ) >& transform ) const
        {
            const auto value = make_string( get( "protocol" ) );
            return transform ? transform( value ) : value;
        }
        
        Bytes Response::get_body( const function< Bytes ( const Bytes& ) >& transform ) const
        {
            const auto value = get( "body" );
            return transform ? transform( value ) : value;
        }
        
        string Response::get_header( const string& name, const string& default_value ) const
        {
            return ( has( name ) ) ? make_string( get( name ) ) : default_value;
        }
        
        string Response::get_header( const string& name, const function< string ( const string& ) >& transform ) const
        {
            const auto value = make_string( get( "header:" + name ) );
            return transform ? transform( value ) : value;
        }
        
        multimap< string, string > Response::get_headers( const string& name ) const
        {
            multimap< string, string > values;
            const string tag = "header:" + name;
            static const string::size_type length = string( "header:" ).length( );
            
            for ( const auto& value : get( ) )
                if ( value.first.find( tag ) not_eq string::npos )
                    values.emplace( value.first.substr( length ), make_string( value.second ) );
                    
            return values;
        }
        
        void Response::set_version( const double value )
        {
            erase( "version" );
            set( "version", make_bytes( ::to_string( value ) ) );
        }
        
        void Response::set_status_code( const int value )
        {
            erase( "status:code" );
            set( "status:code", make_bytes( ::to_string( value ) ) );
        }
        
        void Response::set_status_message( const string& value )
        {
            erase( "status:message" );
            set( "status:message", make_bytes( value ) );
        }
        
        void Response::set_protocol( const string& value )
        {
            erase( "protocol" );
            set( "protocol", make_bytes( value ) );
        }
        
        void Response::set_body( const string& value )
        {
            erase( "body" );
            set( "body", make_bytes( value ) );
        }
        
        void Response::set_body( const Bytes& value )
        {
            erase( "body" );
            set( "body", value );
        }
        
        void Response::set_header( const string& name, const string& value )
        {
            erase( "header:" + name );
            set( "header:" + name, make_bytes( value ) );
        }
        
        void Response::set_headers( const multimap< string, string >& values )
        {
            for ( const auto& value : get( ) )
                if ( value.first.find( "header:" ) not_eq string::npos )
                    erase( value.first );
                    
            for ( const auto& value : values )
                set( "header:" + value.first, make_bytes( value.second ) );
        }
    }
}
