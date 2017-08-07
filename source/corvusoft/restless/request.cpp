/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <stdexcept>

//Project Includes
#include "corvusoft/restless/request.hpp"

//External Includes

//System Namespaces
using std::stoi;
using std::stod;
using std::string;
using std::to_string;
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
        Request::Request( void ) : protocol::Message( )
        {
            return;
        }
        
        Request::~Request( void )
        {
            return;
        }
        
        double Request::get_version( void ) const
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
        
        Bytes Request::get_body( void ) const
        {
            return get( "body" );
        }
        
        string Request::get_path( void ) const
        {
            return make_string( get( "path" ) );
        }
        
        string Request::get_method( void ) const
        {
            return make_string( get( "method" ) );
        }
        
        string Request::get_protocol( void ) const
        {
            return make_string( get( "protocol" ) );
        }
        
        string Request::get_header( const string& name ) const
        {
            return make_string( get( "header:" + name ) );
        }
        
        multimap< string, string > Request::get_headers( void ) const
        {
            multimap< string, string > values;
            const string tag = "header:";
            
            for ( const auto& value : get( ) )
                if ( value.first.find( tag ) not_eq string::npos )
                    values.emplace( value.first.substr( tag.length( ) ), make_string( value.second ) );
                    
            return values;
        }
        
        string Request::get_query_parameter( const string& name ) const
        {
            return make_string( get( "query:" + name ) );
        }
        
        multimap< string, string > Request::get_query_parameters( void ) const
        {
            multimap< string, string > values;
            const string tag = "query:";
            
            for ( const auto& value : get( ) )
                if ( value.first.find( tag ) not_eq string::npos )
                    values.emplace( value.first.substr( tag.length( ) ), make_string( value.second ) );
                    
            return values;
        }
        
        void Request::set_version( const double value )
        {
            erase( "version" );
            set( "version", make_bytes( ::to_string( value ) ) );
        }
        
        void Request::set_body( const Bytes& value )
        {
            erase( "body" );
            set( "body", value );
        }
        
        void Request::set_body( const string& value )
        {
            erase( "body" );
            set( "body", make_bytes( value ) );
        }
        
        void Request::set_path( const string& value )
        {
            erase( "path" );
            set( "path", make_bytes( value ) );
        }
        
        void Request::set_method( const string& value )
        {
            erase( "method" );
            set( "method", make_bytes( value ) );
        }
        
        void Request::set_protocol( const string& value )
        {
            erase( "protocol" );
            set( "protocol", make_bytes( value ) );
        }
        
        void Request::set_header( const string& name, const string& value )
        {
            const auto tag = "header:" + name;
            erase( tag );
            set( tag, make_bytes( value ) );
        }
        
        void Request::set_headers( const multimap< string, string >& values )
        {
            for ( const auto& value : get( ) )
                if ( value.first.find( "header:" ) not_eq string::npos )
                    erase( value.first );
                    
            for ( const auto& value : values )
                set( "header:" + value.first, make_bytes( value.second ) );
        }
        
        void Request::set_query_parameter( const string& name, const string& value )
        {
            const auto tag = "query:" + name;
            erase( tag );
            set( tag, make_bytes( value ) );
        }
        
        void Request::set_query_parameters( const multimap< string, string >& values )
        {
            for ( const auto& value : get( ) )
                if ( value.first.find( "query:" ) not_eq string::npos )
                    erase( value.first );
                    
            for ( const auto& value : values )
                set( "query:" + value.first, make_bytes( value.second ) );
        }
    }
}
