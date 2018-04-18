//System Includes
#include <map>
#include <memory>

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::map;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces

TEST_CASE( "Assert default getter state." )
{
    auto session = make_shared< Session >( );
    REQUIRE( session->get_settings( ) == nullptr );
    REQUIRE( session->get_default_headers( ).empty( ) );
}
