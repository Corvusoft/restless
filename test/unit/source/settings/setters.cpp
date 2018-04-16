//System Includes
#include <memory>
#include <string>
#include <chrono>

//Project Includes
#include <corvusoft/restless/settings.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::make_shared;
using std::chrono::milliseconds;

//Project Namespaces
using corvusoft::restless::Settings;

//External Namespaces

TEST_CASE( "Assert default setter state." )
{
    auto settings = make_shared< Settings >( );
    REQUIRE_NOTHROW( settings->set_port( -45 ) );
    REQUIRE_NOTHROW( settings->set_port( 0 ) );
    REQUIRE_NOTHROW( settings->set_port( 6565 ) );
    
    REQUIRE_NOTHROW( settings->set_address( "" ) );
    REQUIRE_NOTHROW( settings->set_address( "::4838" ) );
    REQUIRE_NOTHROW( settings->set_address( "12.2.23.1" ) );
    
    REQUIRE_NOTHROW( settings->set_bind_address( "" ) );
    REQUIRE_NOTHROW( settings->set_bind_address( "::1" ) );
    REQUIRE_NOTHROW( settings->set_bind_address( "12.0.0.1" ) );
    
    REQUIRE_NOTHROW( settings->set_connection_timeout( milliseconds::min( ) ) );
    REQUIRE_NOTHROW( settings->set_connection_timeout( milliseconds::zero( ) ) );
    REQUIRE_NOTHROW( settings->set_connection_timeout( milliseconds::max( ) ) );
}
