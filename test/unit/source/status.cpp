//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restless/status.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using corvusoft::restless::CONTINUE;
using corvusoft::restless::is_success;
using corvusoft::restless::is_redirection;
using corvusoft::restless::is_client_error;
using corvusoft::restless::is_server_error;
using corvusoft::restless::is_informational;
using corvusoft::restless::status;
using corvusoft::restless::make_status_code;
using corvusoft::restless::make_status_message;

//External Namespaces

TEST_CASE( "Status messages can be altered." )
{
    status.at( CONTINUE ) = "Proceed with HTTP request";
    status.clear( );
    status = map< int, string >( );
    REQUIRE( true );
}

TEST_CASE( "Detect informational status code." )
{
    REQUIRE( is_informational( 100 ) );
    REQUIRE( is_informational( 150 ) ); //random number between 100, 199
    REQUIRE( is_informational( 199 ) );
}

TEST_CASE( "Detect successful status code." )
{
    REQUIRE( is_success( 200 ) );
    REQUIRE( is_success( 250 ) );
    REQUIRE( is_success( 299 ) );
}

TEST_CASE( "Detect redirectional status code." )
{
    REQUIRE( is_redirection( 300 ) );
    REQUIRE( is_redirection( 350 ) );
    REQUIRE( is_redirection( 399 ) );
}

TEST_CASE( "Detect client error status code." )
{
    REQUIRE( is_client_error( 400 ) );
    REQUIRE( is_client_error( 450 ) );
    REQUIRE( is_client_error( 499 ) );
}

TEST_CASE( "Detect server error status code." )
{
    REQUIRE( is_server_error( 500 ) );
    REQUIRE( is_server_error( 550 ) );
    REQUIRE( is_server_error( 599 ) );
}

TEST_CASE( "Convert status message to status code." )
{
    status = map< int, string >
    {
        { 1234, "test status message" },
        { 5678, "another test status message" }
    };

    REQUIRE( make_status_code( "test status message" ) == 1234 );
    REQUIRE( make_status_code( "TEST STATUS MESSAGE" ) == 0 );
    
    REQUIRE( make_status_code( "another test status message" ) == 5678 );
    REQUIRE( make_status_code( "ANOTHER TEST STATUS MESSAGE" ) == 0 );

    REQUIRE( make_status_code( "unknown test status message" ) == 0 );
}

TEST_CASE( "Convert status code to status message." )
{
    status = map< int, string >
    {
        { 1234, "test status message" },
        { 5678, "another test status message" }
    };

    REQUIRE( make_status_message( 1234 ) == "test status message" );
    REQUIRE( make_status_message( 5678 ) == "another test status message" );
    REQUIRE( make_status_message( 0 ) == "" );
    REQUIRE( make_status_message( 876543 ) == "" );
}
