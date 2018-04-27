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

TEST_CASE( "Assert instance has header." )
{
    auto response = make_shared< Response >( );
    response->set_header( "Accept", "application/vnd+xml" );
    REQUIRE( response->has_header( "Accept" ) );
    
    multimap< string, string > values = { { "Host", "corvusoft.com.au" } };
    response->set_headers( values );
    REQUIRE( response->has_header( "Host" ) );
    REQUIRE( response->has_header( "Accept" ) == false );
}
