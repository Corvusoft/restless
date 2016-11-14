/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>

//Project Includes
#include "corvusoft/restless/session.hpp"
#include "corvusoft/restless/detail/session_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::function;
using std::multimap;
using std::shared_ptr;

//Project Namespaces
using restless::detail::SessionImpl;

//External Namespaces

namespace restless
{
    Session::Session( void ) : m_pimpl( new SessionImpl )
    {
        return;
    }
    
    Session::Session( const shared_ptr< const Settings >& ) : m_pimpl( new SessionImpl )
    {
        return;
    }
    
    Session::~Session( void )
    {
        return;
    }
    
    void Session::close( void )
    {
    
    }
    
    bool Session::is_open( void ) const
    {
        return false;
    }
    
    bool Session::is_closed( void ) const
    {
        return true;
    }
    
    void Session::yield( const Bytes& )
    {
    
    }
    
    void Session::yield( const string& )
    {
    
    }
    
    void Session::yield( const Bytes&, const function< void ( const shared_ptr< Session > ) >& )
    {
    
    }
    
    void Session::yield( const string&, const function< void ( const shared_ptr< Session > ) >& )
    {
    
    }
    
    void Session::fetch( const size_t )
    {
    
    }
    
    void Session::fetch( const string& )
    {
    
    }
    
    void Session::fetch( const size_t, const function< void ( const shared_ptr< Session > ) >& )
    {
    
    }
    
    void Session::fetch( const string&, const function< void ( const shared_ptr< Session > ) >& )
    {
    
    }
    
    const shared_ptr< Response > Session::send( const shared_ptr< Request >&, const function< void ( const shared_ptr< Session > ) >& )
    {
        return nullptr;
    }
    
    const shared_ptr< Response > Session::send( const shared_ptr< Request >&, const function< void ( const shared_ptr< Session > ) >&, const function< void ( const shared_ptr< Session > ) >& )
    {
        return nullptr;
    }
    
    void Session::wait( const function< void ( const shared_ptr< Session > ) >& callback )
    {
    
    }
    
    const shared_ptr< Request > Session::get_request( void ) const
    {
        return nullptr;
    }
    
    const shared_ptr< Response > Session::get_response( void ) const
    {
        return nullptr;
    }
    
    const multimap< string, string > Session::get_headers( void ) const
    {
        return multimap< string, string >( );
    }
    
    void Session::add_header( const string& name, const string& value )
    {
    
    }
    
    void Session::set_header( const string& name, const string& value )
    {
    
    }
    
    void Session::set_headers( const multimap< string, string >& values )
    {
    
    }
}
