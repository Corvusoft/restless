//System Includes

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces

TEST_CASE( "Destroy class instance." )
{
    const auto session = new Session( );
    REQUIRE_NOTHROW( delete session );
}