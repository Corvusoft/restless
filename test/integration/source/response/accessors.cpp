//System Includes
#include <map>
#include <memory>
#include <string>

//Project Includes
#include <corvusoft/restless/response.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Response;

//External Namespaces
using corvusoft::core::make_bytes;

TEST_CASE( "Assert instance accessors." )
{
    auto response = make_shared< Response >( );
    response->set_version( 1.0 );
    REQUIRE( response->get_version( ) == 1.0 );
    
    response->set_status_code( 301 );
    REQUIRE( response->get_status_code( ) == 301 );
    
    response->set_status_message( "OK" );
    REQUIRE( response->get_status_message( ) == "OK" );
    
    response->set_protocol( "SPDY" );
    REQUIRE( response->get_protocol( ) == "SPDY" );
    
    response->set_body( "This is my payload." );
    REQUIRE( response->get_body( ) == make_bytes( "This is my payload." ) );
    
    response->set_body( make_bytes( "This is my data payload." ) );
    REQUIRE( response->get_body( ) == make_bytes( "This is my data payload." ) );
    
    response->set_header( "Accept", "application/vnd+xml" );
    multimap< string, string > values = { { "Accept", "application/vnd+xml" } };
    REQUIRE( response->get_headers( ) == values );
    
    values = { { "Host", "corvusoft.com.au" } };
    response->set_headers( values );
    REQUIRE( response->get_headers( ) == values );
}
