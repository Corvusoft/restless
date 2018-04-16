//System Includes

//Project Includes
#include <corvusoft/restless/response.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::restless::Response;

//External Namespaces

TEST_CASE( "Create class instance." )
{
    REQUIRE_NOTHROW( Response( ) );
}
