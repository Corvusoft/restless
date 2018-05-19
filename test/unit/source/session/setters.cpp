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

TEST_CASE( "Assert default setter state." )
{
    auto session = make_shared< Session >( );
    REQUIRE_NOTHROW( session->set_default_header( "", "" ) );
    REQUIRE_NOTHROW( session->set_default_header( "Host", "" ) );
    REQUIRE_NOTHROW( session->set_default_header( "", "http://corvusoft.co.uk" ) );
    REQUIRE_NOTHROW( session->set_default_header( "Host", "http://corvusoft.co.uk" ) );
    
    function< string ( void ) > computed_header = nullptr;
    REQUIRE_NOTHROW( session->set_default_header( "", computed_header ) );
    REQUIRE_NOTHROW( session->set_default_header( "Host", computed_header ) );
    computed_header = [ ]( void )
    {
        return "";
    };
    REQUIRE_NOTHROW( session->set_default_header( "", computed_header ) );
    REQUIRE_NOTHROW( session->set_default_header( "Host", computed_header ) );
    
    multimap< string, string > values;
    REQUIRE_NOTHROW( session->set_default_headers( values ) );
    values = { { "", "" } };
    REQUIRE_NOTHROW( session->set_default_headers( values ) );
    values = { { "Content-Type", "" } };
    REQUIRE_NOTHROW( session->set_default_headers( values ) );
    values = { { "", "application/vnd+json" } };
    REQUIRE_NOTHROW( session->set_default_headers( values ) );
    values = { { "Content-Type", "application/vnd+json" } };
    REQUIRE_NOTHROW( session->set_default_headers( values ) );
}
