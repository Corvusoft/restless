//System Includes
#include <chrono>
#include <memory>
#include <string>
#include <cstdint>

//Project Includes
#include <corvusoft/restless/settings.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::uint16_t;
using std::make_shared;
using std::chrono::milliseconds;

//Project Namespaces
using corvusoft::restless::Settings;

//External Namespaces

TEST_CASE( "Assert instance accessors." )
{
    auto settings = make_shared< Settings >( );
    settings->set_port( 1894 );
    settings->set_address( "::1" );
    settings->set_bind_address( "127.0.0.1" );
    settings->set_connection_timeout( milliseconds( 12 ) );
    REQUIRE( settings->get_port( ) == 1894 );
    REQUIRE( settings->get_address( ) == "::1" );
    REQUIRE( settings->get_bind_address( ) == "127.0.0.1" );
    REQUIRE( settings->get_connection_timeout( ) == milliseconds( 12 ) );
    
    settings->set_port( 8080 );
    settings->set_address( "198.182.123.2" );
    settings->set_bind_address( "a;j084lsfjsdkl" );
    settings->set_connection_timeout( milliseconds( 867756 ) );
    REQUIRE( settings->get_port( ) == 8080 );
    REQUIRE( settings->get_address( ) == "198.182.123.2" );
    REQUIRE( settings->get_bind_address( ) == "a;j084lsfjsdkl" );
    REQUIRE( settings->get_connection_timeout( ) == milliseconds( 867756 ) );
}
