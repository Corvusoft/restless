//System Includes
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <system_error>

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::function;
using std::error_code;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces

TEST_CASE( "Set-up session instance." )
{
    REQUIRE_NOTHROW( Session( ) );
    
    const auto session = make_shared< Session >( );
    REQUIRE( session->is_open( ) == false );
    REQUIRE( session->is_closed( ) == true );
    REQUIRE( session->get_settings( ) == nullptr );
    REQUIRE( session->get_runloop( ) == nullptr );
    REQUIRE( session->get_adaptor( ) == nullptr );
    REQUIRE( session->get_protocol( ) == nullptr );
    REQUIRE( session->get_default_headers( ).empty( ) );
    REQUIRE( session->get_log_handler( ) == nullptr );
    REQUIRE( session->get_connection_timeout_handler( ) == nullptr );
    REQUIRE( session->get_error_handler( ) == nullptr );
}

TEST_CASE( "Clean-up session instance." )
{
    const auto session = new Session;
    REQUIRE_NOTHROW( delete session );
}

TEST_CASE( "Modify session instance." )
{
    const auto session = make_shared< Session >( );
    session->set_default_header( "HDR1", "VALUE1" );
    session->set_default_header( "HDR1", "VALUE2" );
    session->set_default_header( "HDR2", "" );
    session->set_default_header( "COMPUTED 1", [ ]( void )
    {
        return "COMPUTED HDR";
    } );
    
    const function< string ( void ) > empty_function = nullptr;
    session->set_default_header( "COMPUTED 2", empty_function );
    
    multimap< string, string > values
    {
        { "HDR2", "" },
        { "HDR1", "VALUE1" },
        { "HDR1", "VALUE2" },
        { "COMPUTED 2", "" },
        { "COMPUTED 1", "COMPUTED HDR" }
    };
    REQUIRE( session->get_default_headers( ) == values );
    
    values = multimap< string, string > { { "DFLTHDR1", "V1" }, { "DFLTHDR1", "V2" } };
    session->set_default_headers( values );
    REQUIRE( session->get_default_headers( ) == values );
    
    session->set_log_handler( [ ]( int, string )
    {
        return error_code( );
    } );
    REQUIRE( session->get_log_handler( ) not_eq nullptr );
    
    session->set_log_handler( nullptr );
    REQUIRE( session->get_log_handler( ) == nullptr );
}
