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
using std::map;
using std::string;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Request;

//External Namespaces
using corvusoft::core::Bytes;

TEST_CASE( "Assert default getter state." )
{
    auto request = make_shared< Request >( );
    REQUIRE( request->get_version( ) == 0 );
    REQUIRE( request->get_body( ).empty( ) );
    REQUIRE( request->get_path( ).empty( ) );
    REQUIRE( request->get_method( ).empty( ) );
    REQUIRE( request->get_protocol( ).empty( ) );
    REQUIRE( request->get_headers( ).empty( ) );
    REQUIRE( request->get_query_parameters( ).empty( ) );
}
