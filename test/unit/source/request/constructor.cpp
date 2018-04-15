//System Includes

//Project Includes
#include <corvusoft/restless/request.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::restless::Request;

//External Namespaces

TEST_CASE( "Create class instance." )
{
    REQUIRE_NOTHROW( Request( ) );
}
