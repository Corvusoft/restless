//System Includes
#include <map>
#include <memory>
#include <string>

//Project Includes
#include <corvusoft/restless/response.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Response;

//External Namespaces

TEST_CASE( "Assert instance accessors." )
{
    auto response = make_shared< Response >( );
    response->set_header( "Content-Type", "application/vnd+yaml" );
    response->set_header( "Content-Type", "application/vnd+json" );
    REQUIRE( response->get_header( "Content-Type" ) == "application/vnd+yaml" );
    REQUIRE( response->get_header( "Content-Type", "application/vnd+txt" ) == "application/vnd+yaml" );
    
    response->set_header( "Content-Length", "13" );
    REQUIRE( response->get_header( "Content-Length", 0 ) == 13 );
    REQUIRE( response->get_header( "Content-Length", 0l ) == 13 );
    REQUIRE( response->get_header( "Content-Length", 0ul ) == 13 );
    
    response->set_header( "Version", "1.1" );
    REQUIRE( response->get_header( "Version", 1.0 ) == 1.1 );
    REQUIRE( response->get_header( "Version", 1.0f ) == 1.1f );
}
