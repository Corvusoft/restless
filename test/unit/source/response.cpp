//System Includes
#include <map>
#include <string>
#include <memory>

//Project Includes
#include <corvusoft/restless/response.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Response;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Set-up response instance." )
{
    REQUIRE_NOTHROW( Response( ) );
    
    const auto response = make_shared< Response >( );
    REQUIRE( response->get_version( ) == 0.0 );
    REQUIRE( response->get_status_code( ) == 0 );
    REQUIRE( response->get_status_message( ).empty( ) );
    REQUIRE( response->get_protocol( ).empty( ) );
    REQUIRE( response->get_body( ).empty( ) );
    REQUIRE( response->get_headers( ).empty( ) );
}

TEST_CASE( "Clean-up response instance." )
{
    const auto response = new Response;
    REQUIRE_NOTHROW( delete response );
}

TEST_CASE( "Modify response instance." )
{
    const auto response = make_shared< Response >( );
    response->set_version( 1.01 );
    REQUIRE( response->get_version( ) == 1.01 );
    
    response->set_status_code( 430 );
    REQUIRE( response->get_status_code( ) == 430 );
    
    response->set_status_message( "My Status Message" );
    REQUIRE( response->get_status_message( ) == "My Status Message" );
    
    response->set_protocol( "SPDY" );
    REQUIRE( response->get_protocol( ) == "SPDY" );
    
    response->set_body( "important data!" );
    REQUIRE( response->get_body( ) == make_bytes( "important data!" ) );
    
    response->set_body( make_bytes( "RO Import" ) );
    REQUIRE( response->get_body( ) == make_bytes( "RO Import" ) );
    
    response->set_header( "Content-Type", "application/yaml" );
    REQUIRE( response->has_header( "Content-Type" ) == true );
    REQUIRE( response->has_header( "Content-Length" ) == false );
    REQUIRE( response->get_header( "Content-Type" ) == "application/yaml" );
    REQUIRE( response->get_header( "Content-Length", 30 ) == 30 );
    REQUIRE( response->get_header( "KEY", "1234" ) == "1234" );
    REQUIRE( response->get_header( "Content-Type", "1234" ) == "application/yaml" );
    REQUIRE( response->get_header( "LINK" ) == "" );
    
    auto values = multimap< string, string >
    {
        { "HDR1", "Value 1"   },
        { "HDR1", "Value One" },
        { "HDR2", "Value Two" }
    };
    response->set_headers( values );
    REQUIRE( response->has_header( "HDR1" ) );
    REQUIRE( response->has_header( "HDR2" ) );
    REQUIRE( response->get_headers( ) == values );
    REQUIRE( response->get_header( "HDR1" ) == "Value 1" );
    REQUIRE( response->get_header( "HDR2" ) == "Value Two" );
    
    values = multimap< string, string >
    {
        { "HDR1", "Value 1"   },
        { "HDR1", "Value One" }
    };
    REQUIRE( response->get_headers( "HDR1" ) == values );
}

TEST_CASE( "Transform response data." )
{
    const auto transform_string = [ ]( const string& )
    {
        return "transformed";
    };
    const auto transform_bytes = [ ]( const Bytes& )
    {
        return make_bytes( "transformed" );
    };
    
    const auto response = make_shared< Response >( );
    response->set_status_message( "My Status Message" );
    REQUIRE( response->get_status_message( nullptr ) == "My Status Message" );
    REQUIRE( response->get_status_message( transform_string ) == "transformed" );
    
    response->set_protocol( "SPDY" );
    REQUIRE( response->get_protocol( nullptr ) == "SPDY" );
    REQUIRE( response->get_protocol( transform_string ) == "transformed" );
    
    response->set_body( "important data!" );
    REQUIRE( response->get_body( nullptr ) == make_bytes( "important data!" ) );
    REQUIRE( response->get_body( transform_bytes ) == make_bytes( "transformed" ) );
    
    response->set_header( "Content-Type", "application/yaml" );
    REQUIRE( response->get_header( "Content-Type", transform_string ) == "transformed" );
}
