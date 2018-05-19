//System Includes
#include <memory>
#include <string>
#include <chrono>

//Project Includes
#include <corvusoft/restless/settings.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::make_shared;
using std::chrono::milliseconds;

//Project Namespaces
using corvusoft::restless::Settings;

//External Namespaces

TEST_CASE( "Assert default getter state." )
{
    auto settings = make_shared< Settings >( );
    REQUIRE( settings->get_port( ) == 80 );
    REQUIRE( settings->get_address( ).empty( ) );
    REQUIRE( settings->get_bind_address( ).empty( ) );
    REQUIRE( settings->get_connection_timeout( ) == milliseconds( 10000 ) );
}
