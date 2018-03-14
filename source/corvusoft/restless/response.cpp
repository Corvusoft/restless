/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restless/response.hpp"
#include "corvusoft/restless/detail/response_impl.hpp"

//External Includes

//System Namespaces
using std::string;
using std::multimap;

//Project Namespaces
using corvusoft::restless::detail::ResponseImpl;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

namespace corvusoft
{
    namespace restless
    {
        Response::Response( void ) : m_pimpl( new ResponseImpl )
        {
            return;
        }
        
        Response::~Response( void )
        {
            return;
        }
        
        bool Response::has_header( const string& name ) const
        {
            return m_pimpl->headers.find( name ) not_eq m_pimpl->headers.end( );
        }
        
        double Response::get_version( void ) const
        {
            return m_pimpl->version;
        }
        
        int Response::get_status_code( void ) const
        {
            return m_pimpl->status;
        }
        
        string Response::get_status_message( void ) const
        {
            return m_pimpl->message;
        }
        
        string Response::get_protocol( void ) const
        {
            return m_pimpl->protocol;
        }
        
        Bytes Response::get_body( void ) const
        {
            return m_pimpl->body;
        }
        
        string Response::get_header( const string& name, const string& default_value ) const
        {
            auto iterator = m_pimpl->headers.find( name );
            if ( iterator == m_pimpl->headers.end( ) ) return default_value;
            return iterator->second;
        }
        
        multimap< string, string > Response::get_headers( const string& name ) const
        {
            return m_pimpl->headers;
        }
        
        void Response::set_version( const double value )
        {
            m_pimpl->version = value;
        }
        
        void Response::set_status_code( const int value )
        {
            m_pimpl->status = value;
        }
        
        void Response::set_status_message( const string& value )
        {
            m_pimpl->message = value;
        }
        
        void Response::set_protocol( const string& value )
        {
            m_pimpl->protocol = value;
        }
        
        void Response::set_body( const string& value )
        {
            m_pimpl->body = make_bytes( value );
        }
        
        void Response::set_body( const Bytes& value )
        {
            m_pimpl->body = value;
        }
        
        void Response::set_header( const string& name, const string& value )
        {
            m_pimpl->headers.emplace( name, value );
        }
        
        void Response::set_headers( const multimap< string, string >& values )
        {
            m_pimpl->headers = values;
        }
    }
}
