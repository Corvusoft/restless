//System Includes
#include <string>
#include <memory>

//Project Includes
#include <corvusoft/restless/request.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Request;

//External Namespaces

TEST_CASE( "Set-up request instance." )
{
    REQUIRE_NOTHROW( Request( ) );

    const auto request = make_shared< Request >( );
    //REQUIRE( settings->get_bind_address( ) == "" );
    //REQUIRE( settings->get_connection_timeout( ) == milliseconds( 10000 ) );
}

TEST_CASE( "Clean-up request instance." )
{
    const auto request = new Request;
    REQUIRE_NOTHROW( delete request );
}
