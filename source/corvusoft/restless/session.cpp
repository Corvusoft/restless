/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>
#include <system_error>

//Project Includes
#include "corvusoft/restless/session.hpp"
#include "corvusoft/restless/detail/session_impl.hpp"

//External Includes
#include "corvusoft/restbed/detail/http_impl.hpp"

//System Namespaces
using std::map;
using std::size_t;
using std::string;
using std::function;
using std::multimap;
using std::error_code;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;

//Project Namespaces
using restless::detail::SessionImpl;

//External Namespaces
using restbed::detail::HttpImpl;

namespace restless
{
    Session::Session( const Uri& uri, const shared_ptr< const Settings >& settings ) : m_pimpl( new SessionImpl( uri, settings ) )
    {
        return;
    }
    
    Session::~Session( void )
    {
        return;
    }
    
    void Session::wait( void )
    {
    
    }
    
    void Session::close( void )
    {
        m_pimpl->close( );
    }
    
    bool Session::is_open( void ) const
    {
        return m_pimpl->m_is_open;
    }
    
    bool Session::is_closed( void ) const
    {
        return not m_pimpl->m_is_open;
    }
    
    Bytes Session::fetch( const size_t length, const function< void ( const shared_ptr< Session > ) >& )
    {
        return m_pimpl->fetch( length );
    }
    
    Bytes Session::fetch( const string& delimiter, const function< void ( const shared_ptr< Session > ) >& )
    {
        return m_pimpl->fetch( delimiter );
    }
    
    const shared_ptr< Response > Session::send( const shared_ptr< Request >& request, const function< void ( const shared_ptr< Session > ) >& response_handler )
    {
        auto data = HttpImpl::to_bytes( request );
        
        if ( response_handler == nullptr )
        {
            error_code error;
            auto response = m_pimpl->sync( data, error );
            
            if ( error )
            {
                close( );
                return m_pimpl->create_error_response( error );
            }
            
            return m_pimpl->parse( response );
        }
        else
        {
        
        }
        
        return nullptr;
    }
    
    const shared_ptr< Response > Session::send( const shared_ptr< Request >&, const function< size_t ( const shared_ptr< Session > ) >&, const function< void ( const shared_ptr< Session > ) >& )
    {
        return nullptr;
    }
    
    const multimap< string, string > Session::get_headers( void ) const
    {
        return m_pimpl->m_headers;
    }
    
    void Session::add_header( const string& name, const string& value )
    {
        m_pimpl->m_headers.insert( make_pair( name, value ) );
    }
    
    void Session::set_header( const string& name, const string& value )
    {
        m_pimpl->m_headers.erase( name );
        add_header( name, value );
    }
    
    void Session::set_headers( const multimap< string, string >& values )
    {
        m_pimpl->m_headers = values;
    }
}
