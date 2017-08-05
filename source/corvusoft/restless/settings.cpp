/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restless/settings.hpp"

//External Includes

//System Namespaces
using std::string;
using std::chrono::milliseconds;

//Project Namespaces

//External Namespaces
using corvusoft::core::Settings;

namespace corvusoft
{
    namespace restless
    {
        Settings::Settings( void ) : core::Settings( )
        {
            return;
        }
        
        Settings::~Settings( void )
        {
            return;
        }
        
        string Settings::get_bind_address( void ) const
        {
            return get( "bind:address" );
        }
        
        milliseconds Settings::get_connection_timeout( void ) const
        {
            return milliseconds( get( "connection:timeout", 10000 ) );
        }
        
        void Settings::set_bind_address( const string& value )
        {
            set( "bind:address", value );
        }
        
        void Settings::set_connection_timeout( const milliseconds& value )
        {
            set( "connection:timeout", value.count( ) );
        }
    }
}
