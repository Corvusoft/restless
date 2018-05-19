//System Includes
#include <map>
#include <memory>
#include <string>
#include <functional>

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::function;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces

TEST_CASE( "Assert instance accessors." )
{
    auto session = make_shared< Session >( );
    session->set_default_header( "Host", "http://corvusoft.co.uk" );
    session->set_default_header( "Date", [ ]( void )
    {
        return "Sat, 28 Apr 2018 07:18:00 GMT";
    } );
    
    multimap< string, string > values
    {
        { "Host", "http://corvusoft.co.uk" },
        { "Date", "Sat, 28 Apr 2018 07:18:00 GMT" }
    };
    REQUIRE( session->get_default_headers( ) == values );
    
    values = { { "Content-Type", "application/vnd+json" } };
    session->set_default_headers( values );
    REQUIRE( session->get_default_headers( ) == values );
}
