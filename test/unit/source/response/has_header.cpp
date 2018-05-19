//System Includes
#include <memory>

//Project Includes
#include <corvusoft/restless/response.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Response;

//External Namespaces

TEST_CASE( "Assert default has header state." )
{
    auto response = make_shared< Response >( );
    REQUIRE_NOTHROW( response->has_header( "" ) );
    REQUIRE_NOTHROW( response->has_header( "Host" ) );
    REQUIRE_NOTHROW( response->has_header( "a;lodjfaq40tu8po0argj;" ) );
}
