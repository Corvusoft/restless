//System Includes
#include <map>
#include <string>
#include <memory>

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces

TEST_CASE( "Set-up session instance." )
{
    REQUIRE_NOTHROW( Session( ) );
    
    const auto session = make_shared< Session >( );
    // REQUIRE( session->get_version( ) == 0.0 );
    // REQUIRE( session->get_body( ).empty( ) );
    // REQUIRE( session->get_path( ).empty( ) );
    // REQUIRE( session->get_method( ).empty( ) );
    // REQUIRE( session->get_protocol( ).empty( ) );
    // REQUIRE( session->get_headers( ).empty( ) );
    // REQUIRE( session->get_query_parameters( ).empty( ) );
}

TEST_CASE( "Clean-up session instance." )
{
    const auto session = new Session;
    REQUIRE_NOTHROW( delete session );
}
