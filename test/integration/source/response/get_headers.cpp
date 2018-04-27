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
    response->set_header( "Accept", "application/vnd+xml" );
    response->set_header( "Accept", "application/vnd+json" );
    response->set_header( "Conent-Type", "application/vnd+json" );
    
    multimap< string, string > values = { { "Accept", "application/vnd+xml" }, { "Accept", "application/vnd+json" } };
    REQUIRE( response->get_headers( "Accept" ) == values );
    
    values = { { "Content-Type", "application/vnd+json" } };
    response->set_headers( values );
    REQUIRE( response->get_headers( "Content-Type" ) == values );
    
    values = { { "Accept", "application/vnd+xml" }, { "Accept", "application/vnd+json" }, { "Content-Type", "application/vnd+json" } };
    response->set_headers( values );
    REQUIRE( response->get_headers( )  == values );
}
