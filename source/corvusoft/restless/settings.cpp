/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restless/settings.hpp"

//External Includes

//System Namespaces
using std::string;
using std::uint16_t;
using std::to_string;
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
        
        uint16_t Settings::get_port( void ) const
        {
            return get( "port", 80 );
        }
        
        string Settings::get_address( void ) const
        {
            return get( "address" );
        }
        
        string Settings::get_bind_address( void ) const
        {
            return get( "bind:address" );
        }
        
        milliseconds Settings::get_connection_timeout( void ) const
        {
            static const auto default_value = milliseconds( 10000 ).count( );
            return milliseconds( get( "connection:timeout", default_value ) );
        }
        
        void Settings::set_port( const uint16_t value )
        {
            set( "port", to_string( value ) );
        }
        
        void Settings::set_address( const string& value )
        {
            set( "address", value );
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
