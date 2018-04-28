//System Includes
#include <map>
#include <memory>
#include <string>

//Project Includes
#include <corvusoft/restless/request.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Request;

//External Namespaces
using corvusoft::core::make_bytes;

TEST_CASE( "Assert instance accessors." )
{
    auto request = make_shared< Request >( );
    request->set_version( 1.0 );
    REQUIRE( request->get_version( ) == 1.0 );
    
    request->set_body( "This is my payload." );
    REQUIRE( request->get_body( ) == make_bytes( "This is my payload." ) );
    
    request->set_body( make_bytes( "This is my data payload." ) );
    REQUIRE( request->get_body( ) == make_bytes( "This is my data payload." ) );
    
    request->set_path( "/resource/1234" );
    REQUIRE( request->get_path( ) == "/resource/1234" );
    
    request->set_method( "PUT" );
    REQUIRE( request->get_method( ) == "PUT" );
    
    request->set_protocol( "SPDY" );
    REQUIRE( request->get_protocol( ) == "SPDY" );
    
    request->set_header( "Accept", "application/vnd+xml" );
    multimap< string, string > values = { { "Accept", "application/vnd+xml" } };
    REQUIRE( request->get_headers( ) == values );
    
    values = { { "Host", "corvusoft.com.au" }, { "Version", "1" } };
    request->set_headers( values );
    REQUIRE( request->get_headers( ) == values );
    
    request->set_query_parameter( "query", "Von%20Neumann%20architecture" );
    values = { { "query", "Von%20Neumann%20architecture" } };
    REQUIRE( request->get_query_parameters( ) == values );
    
    values = { { "api", "1.2a" }, { "rev", "31" } };
    request->set_query_parameters( values );
    REQUIRE( request->get_query_parameters( ) == values );
}
