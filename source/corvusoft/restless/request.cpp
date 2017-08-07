/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restless/request.hpp"

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
        
        }
        
        Bytes Request::get_body( void ) const
        {
        
        }
        
        string Request::get_path( void ) const
        {
        
        }
        
        string Request::get_method( void ) const
        {
        
        }
        
        string Request::get_protocol( void ) const
        {
            //validate against protocols wehn sending.
        }
        
        string Request::get_header( const string& name ) const
        {
        
        }
        
        multimap< string, string > Request::get_headers( void ) const
        {
        
        }
        
        string Request::get_query_parameter( const string& name ) const
        {
        
        }
        
        multimap< string, string > Request::get_query_parameters( void ) const
        {
        
        }
        
        void Request::set_version( const double value )
        {
        
        }
        
        void Request::set_body( const Bytes& value )
        {
        
        }
        
        void Request::set_body( const string& value )
        {
        
        }
        
        void Request::set_path( const string& value )
        {
        
        }
        
        void Request::set_method( const string& value )
        {
        
        }
        
        void Request::set_protocol( const string& value )
        {
        
        }
        
        void Request::set_header( const string& name, const string& value )
        {
        
        }
        
        void Request::set_headers( const multimap< string, string >& values )
        {
        
        }
        
        void set_query_parameter( const string& name, const string& value )
        {
        
        }
        
        void set_query_parameters( const multimap< string, string >& values )
        {
        
        }
    }
}
