//System Includes

//Project Includes
#include <corvusoft/restless/settings.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::restless::Settings;

//External Namespaces

TEST_CASE( "Destroy class instance." )
{
    const auto settings = new Settings( );
    REQUIRE_NOTHROW( delete settings );
}
