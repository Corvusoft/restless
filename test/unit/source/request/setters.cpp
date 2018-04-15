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
using std::string;
using std::multimap;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Request;

//External Namespaces
using corvusoft::core::Bytes;

TEST_CASE( "Assert default setter state." )
{
    auto request = make_shared< Request >( );
    REQUIRE_NOTHROW( request->set_version( -13.1 ) );
    REQUIRE_NOTHROW( request->set_version( 0 ) );
    REQUIRE_NOTHROW( request->set_version( 1.0 ) );
    REQUIRE_NOTHROW( request->set_version( 1.1 ) );
    REQUIRE_NOTHROW( request->set_version( 56.1233 ) );
    
    REQUIRE_NOTHROW( request->set_body( "" ) );
    REQUIRE_NOTHROW( request->set_body( "data value." ) );
    REQUIRE_NOTHROW( request->set_body( Bytes{ } ) );
    REQUIRE_NOTHROW( request->set_body( Bytes{ 'd', 'a', 't', 'a' } ) );
    
    REQUIRE_NOTHROW( request->set_path( "" ) );
    REQUIRE_NOTHROW( request->set_path( "/resource/1" ) );
    
    REQUIRE_NOTHROW( request->set_method( "" ) );
    REQUIRE_NOTHROW( request->set_method( "DELETE" ) );
    
    REQUIRE_NOTHROW( request->set_protocol( "" ) );
    REQUIRE_NOTHROW( request->set_protocol( "HTTP" ) );
    
    REQUIRE_NOTHROW( request->set_header( "", "" ) );
    REQUIRE_NOTHROW( request->set_header( "Host", "" ) );
    REQUIRE_NOTHROW( request->set_header( "", "http://corvusoft.co.uk" ) );
    REQUIRE_NOTHROW( request->set_header( "Host", "http://corvusoft.co.uk" ) );
    
    multimap< string, string > values;
    REQUIRE_NOTHROW( request->set_headers( values ) );
    values = { { "", "" } };
    REQUIRE_NOTHROW( request->set_headers( values ) );
    values = { { "Content-Type", "" } };
    REQUIRE_NOTHROW( request->set_headers( values ) );
    values = { { "", "application/vnd+json" } };
    REQUIRE_NOTHROW( request->set_headers( values ) );
    values = { { "Content-Type", "application/vnd+json" } };
    REQUIRE_NOTHROW( request->set_headers( values ) );
    
    values = { };
    REQUIRE_NOTHROW( request->set_query_parameters( values ) );
    values = { { "", "" } };
    REQUIRE_NOTHROW( request->set_query_parameters( values ) );
    values = { { "Content-Type", "" } };
    REQUIRE_NOTHROW( request->set_query_parameters( values ) );
    values = { { "", "application/vnd+json" } };
    REQUIRE_NOTHROW( request->set_query_parameters( values ) );
    values = { { "Content-Type", "application/vnd+json" } };
    REQUIRE_NOTHROW( request->set_query_parameters( values ) );
}
