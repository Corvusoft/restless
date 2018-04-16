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
using std::map;
using std::string;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Response;

//External Namespaces
using corvusoft::core::Bytes;

TEST_CASE( "Assert default getter state." )
{
    auto response = make_shared< Response >( );
    REQUIRE( response->get_version( ) == 0 );
    REQUIRE( response->get_status_code( ) == 0 );
    REQUIRE( response->get_status_message( ).empty( ) );
    REQUIRE( response->get_body( ).empty( ) );
    REQUIRE( response->get_protocol( ).empty( ) );
    REQUIRE( response->get_header( "" ).empty( ) );
    REQUIRE( response->get_header( "Host" ).empty( ) );
    REQUIRE( response->get_headers( ).empty( ) );
}
