//System Includes
#include <map>
#include <string>
#include <memory>

//Project Includes
#include <corvusoft/restless/request.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Request;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Set-up request instance." )
{
    REQUIRE_NOTHROW( Request( ) );
    
    const auto request = make_shared< Request >( );
    REQUIRE( request->get_version( ) == 0.0 );
    REQUIRE( request->get_body( ).empty( ) );
    REQUIRE( request->get_path( ).empty( ) );
    REQUIRE( request->get_method( ).empty( ) );
    REQUIRE( request->get_protocol( ).empty( ) );
    REQUIRE( request->get_headers( ).empty( ) );
    REQUIRE( request->get_query_parameters( ).empty( ) );
}

TEST_CASE( "Clean-up request instance." )
{
    const auto request = new Request;
    REQUIRE_NOTHROW( delete request );
}

TEST_CASE( "Modify request instance." )
{
    const auto request = make_shared< Request >( );
    request->set_version( 1.01 );
    REQUIRE( request->get_version( ) == 1.01 );
    
    request->set_body( "important data!" );
    REQUIRE( request->get_body( ) == make_bytes( "important data!" ) );
    
    request->set_body( make_bytes( "RO Import" ) );
    REQUIRE( request->get_body( ) == make_bytes( "RO Import" ) );
    
    request->set_path( "/root/resource" );
    REQUIRE( request->get_path( ) == "/root/resource" );
    
    request->set_path( "PATCH" );
    REQUIRE( request->get_path( ) == "PATCH" );
    
    request->set_protocol( "SPDY" );
    REQUIRE( request->get_protocol( ) == "SPDY" );
    
    request->set_header( "Content-Type", "application/yaml" );
    REQUIRE( request->get_header( "Content-Type" ) == "application/yaml" );
    REQUIRE( request->get_header( "LINK" ) == "" );
    
    multimap< string, string > values = { { "Content-Type", "application/yaml" } };
    REQUIRE( request->get_headers( ) == values );
    
    values = multimap< string, string >
    {
        { "HDR1", "Value 1"   },
        { "HDR1", "Value One" },
        { "HDR2", "Value Two" }
    };
    request->set_headers( values );
    REQUIRE( request->get_headers( ) == values );
    REQUIRE( request->get_header( "HDR1" ) == "Value 1" );
    REQUIRE( request->get_header( "HDR2" ) == "Value Two" );
    
    request->set_query_parameter( "q", "C++ RESTful clients" );
    REQUIRE( request->get_query_parameter( "q" ) == "C++ RESTful clients" );
    REQUIRE( request->get_query_parameter( "u" ) == "" );
    
    values = multimap< string, string >
    {
        { "QRY1", "Value 1"   },
        { "QRY1", "Value One" },
        { "QRY2", "Value Two" }
    };
    request->set_query_parameters( values );
    REQUIRE( request->get_query_parameters( ) == values );
    REQUIRE( request->get_query_parameter( "QRY1" ) == "Value 1" );
    REQUIRE( request->get_query_parameter( "QRY2" ) == "Value Two" );
}
