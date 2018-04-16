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
using corvusoft::core::Bytes;

TEST_CASE( "Assert default setter state." )
{
    auto response = make_shared< Response >( );
    REQUIRE_NOTHROW( response->set_version( -13.1 ) );
    REQUIRE_NOTHROW( response->set_version( 0 ) );
    REQUIRE_NOTHROW( response->set_version( 1.0 ) );
    REQUIRE_NOTHROW( response->set_version( 1.1 ) );
    REQUIRE_NOTHROW( response->set_version( 56.1233 ) );
    
    REQUIRE_NOTHROW( response->set_status_code( -1 ) );
    REQUIRE_NOTHROW( response->set_status_code( 200 ) );
    REQUIRE_NOTHROW( response->set_status_code( 900239 ) );
    
    REQUIRE_NOTHROW( response->set_status_message( "" ) );
    REQUIRE_NOTHROW( response->set_status_message( "Continue" ) );
    
    REQUIRE_NOTHROW( response->set_body( "" ) );
    REQUIRE_NOTHROW( response->set_body( "data value." ) );
    REQUIRE_NOTHROW( response->set_body( Bytes{ } ) );
    REQUIRE_NOTHROW( response->set_body( Bytes{ 'd', 'a', 't', 'a' } ) );
    
    REQUIRE_NOTHROW( response->set_protocol( "" ) );
    REQUIRE_NOTHROW( response->set_protocol( "HTTP" ) );
    
    REQUIRE_NOTHROW( response->set_header( "", "" ) );
    REQUIRE_NOTHROW( response->set_header( "Host", "" ) );
    REQUIRE_NOTHROW( response->set_header( "", "http://corvusoft.co.uk" ) );
    REQUIRE_NOTHROW( response->set_header( "Host", "http://corvusoft.co.uk" ) );
    
    multimap< string, string > values;
    REQUIRE_NOTHROW( response->set_headers( values ) );
    values = { { "", "" } };
    REQUIRE_NOTHROW( response->set_headers( values ) );
    values = { { "Content-Type", "" } };
    REQUIRE_NOTHROW( response->set_headers( values ) );
    values = { { "", "application/vnd+json" } };
    REQUIRE_NOTHROW( response->set_headers( values ) );
    values = { { "Content-Type", "application/vnd+json" } };
    REQUIRE_NOTHROW( response->set_headers( values ) );
}
