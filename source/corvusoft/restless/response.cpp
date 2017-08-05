/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restless/status.hpp"
#include "corvusoft/restless/response.hpp"

//External Includes

//System Namespaces
using std::string;
using std::function;
using std::multimap;

//Project Namespaces

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;
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
            return has( "request:header:" + name );
        }
        
        double Response::get_version( void ) const
        {
            //remeber locale bug!
            //should the logic remain in the protocol? yes i'd say.
        }
        
        int Response::get_status_code( void ) const
        {
        
        }
        
        string Response::get_status_message( const function< string ( const string& ) >& transform ) const
        {
            
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
        
        multimap< const string, const string > Response::get_headers( const string& name ) const
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
        
        void Response::set_headers( const multimap< const string, const string >& values )
        {
            //erase( "header:" + name );
            //add_header( name, value );
        }
    }
}
