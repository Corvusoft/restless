/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <stdexcept>

//Project Includes
#include "corvusoft/restless/request.hpp"
#include "corvusoft/restless/detail/request_impl.hpp"

//External Includes

//System Namespaces
using std::string;
using std::multimap;

//Project Namespaces
using corvusoft::restless::detail::RequestImpl;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

namespace corvusoft
{
    namespace restless
    {
        Request::Request( void ) : m_pimpl( new RequestImpl )
        {
            return;
        }
        
        Request::~Request( void )
        {
            return;
        }
        
        double Request::get_version( void ) const
        {
            return m_pimpl->version;
        }
        
        Bytes Request::get_body( void ) const
        {
            return m_pimpl->body;
        }
        
        string Request::get_path( void ) const
        {
            return m_pimpl->path;
        }
        
        string Request::get_method( void ) const
        {
            return m_pimpl->method;
        }
        
        string Request::get_protocol( void ) const
        {
            return m_pimpl->protocol;
        }
        
        string Request::get_header( const string& name ) const
        {
            auto iterator = m_pimpl->headers.find( name );
            if ( iterator == m_pimpl->headers.end( ) ) return "";
            return iterator->second;
        }
        
        multimap< string, string > Request::get_headers( void ) const
        {
            return m_pimpl->headers;
        }
        
        string Request::get_query_parameter( const string& name ) const
        {
            auto iterator = m_pimpl->parameters.find( name );
            if ( iterator == m_pimpl->parameters.end( ) ) return "";
            return iterator->second;
        }
        
        multimap< string, string > Request::get_query_parameters( void ) const
        {
            return m_pimpl->parameters;
        }
        
        void Request::set_version( const double value )
        {
            m_pimpl->version = value;
        }
        
        void Request::set_body( const Bytes& value )
        {
            m_pimpl->body = value;
        }
        
        void Request::set_body( const string& value )
        {
            m_pimpl->body = make_bytes( value );
        }
        
        void Request::set_path( const string& value )
        {
            m_pimpl->path = value;
        }
        
        void Request::set_method( const string& value )
        {
            m_pimpl->method = value;
        }
        
        void Request::set_protocol( const string& value )
        {
            m_pimpl->protocol = value;
        }
        
        void Request::set_header( const string& name, const string& value )
        {
            m_pimpl->headers.emplace( name, value );
        }
        
        void Request::set_headers( const multimap< string, string >& values )
        {
            m_pimpl->headers = values;
        }
        
        void Request::set_query_parameter( const string& name, const string& value )
        {
            m_pimpl->parameters.emplace( name, value );
        }
        
        void Request::set_query_parameters( const multimap< string, string >& values )
        {
            m_pimpl->parameters = values;
        }
    }
}
