//System Includes

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces

TEST_CASE( "Create class instance." )
{
    REQUIRE_NOTHROW( Session( ) );
}
