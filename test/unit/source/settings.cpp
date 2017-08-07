//System Includes
#include <string>
#include <chrono>
#include <memory>

//Project Includes
#include <corvusoft/restless/settings.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::chrono::milliseconds;

//Project Namespaces
using corvusoft::restless::Settings;

//External Namespaces

TEST_CASE( "Set-up settings instance." )
{
    REQUIRE_NOTHROW( Settings( ) );

    const auto settings = make_shared< Settings >( );
    REQUIRE( settings->get_bind_address( ) == "" );
    REQUIRE( settings->get_connection_timeout( ) == milliseconds( 10000 ) );
}

TEST_CASE( "Clean-up settings instance." )
{
    const auto settings = new Settings;
    REQUIRE_NOTHROW( delete settings );
}

TEST_CASE( "Modify settings instance." )
{
    const auto settings = make_shared< Settings >( );
    settings->set_bind_address( "127.0.0.1" );
    REQUIRE( settings->get_bind_address( ) == "127.0.0.1" );

    settings->set_bind_address( "::1" );
    REQUIRE( settings->get_bind_address( ) == "::1" );

    settings->set_bind_address( "" );
    REQUIRE( settings->get_bind_address( ) == "" );

    settings->set_connection_timeout( milliseconds( 5000 ) );
    REQUIRE( settings->get_connection_timeout( ) == milliseconds( 5000 ) );

    settings->set_connection_timeout( milliseconds( 800 ) );
    REQUIRE( settings->get_connection_timeout( ) == milliseconds( 800 ) );

    settings->set_connection_timeout( milliseconds::min( ) );
    REQUIRE( settings->get_connection_timeout( ) == milliseconds::min( ) );

    settings->set_connection_timeout( milliseconds::max( ) );
    REQUIRE( settings->get_connection_timeout( ) == milliseconds::max( ) );

    settings->set_connection_timeout( milliseconds::zero( ) );
    REQUIRE( settings->get_connection_timeout( ) == milliseconds::zero( ) );

    settings->set_connection_timeout( milliseconds( 10000 ) );
    REQUIRE( settings->get_connection_timeout( ) == milliseconds( 10000 ) );
}
