//System Includes
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
using std::function;
using std::error_code;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces

TEST_CASE( "Assert invalid open parameters." )
{
    auto session = make_shared< Session >( );
    REQUIRE_NOTHROW( session->open( nullptr, nullptr ) );
    REQUIRE_NOTHROW( session->open( nullptr, [ ]( auto, auto )
    {
        return error_code( );
    } ) );
    REQUIRE_NOTHROW( session->open( "", -12232, nullptr ) );
    REQUIRE_NOTHROW( session->open( "", 0, nullptr ) );
    REQUIRE_NOTHROW( session->open( "", 34463, [ ]( auto, auto )
    {
        return error_code( );
    } ) );
    REQUIRE_NOTHROW( session->open( "::1", -12232, nullptr ) );
    REQUIRE_NOTHROW( session->open( "::1", 0, nullptr ) );
    REQUIRE_NOTHROW( session->open( "::1", 34463, [ ]( auto, auto )
    {
        return error_code( );
    } ) );
    REQUIRE_NOTHROW( session->open( "198.34.23.23", -12232, nullptr ) );
    REQUIRE_NOTHROW( session->open( "198.34.23.23", 0, nullptr ) );
    REQUIRE_NOTHROW( session->open( "198.34.23.23", 34463, [ ]( auto, auto )
    {
        return error_code( );
    } ) );
    REQUIRE_NOTHROW( session->open( "www.corvusoft.co.uk", -12232, nullptr ) );
    REQUIRE_NOTHROW( session->open( "www.corvusoft.co.uk", 0, nullptr ) );
    REQUIRE_NOTHROW( session->open( "www.corvusoft.co.uk", 34463, [ ]( auto, auto )
    {
        return error_code( );
    } ) );
}
