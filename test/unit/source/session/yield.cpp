//System Includes
#include <string>
#include <memory>
#include <functional>
#include <system_error>

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::string;
using std::function;
using std::error_code;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces
using corvusoft::core::make_bytes;

TEST_CASE( "Assert invalid yield parameters." )
{
    auto session = make_shared< Session >( );
    REQUIRE_NOTHROW( session->yield( "", nullptr ) );
    REQUIRE_NOTHROW( session->yield( "", [ ]( auto, auto )
    {
        return error_code( );
    } ) );
    REQUIRE_NOTHROW( session->yield( "my payload.", nullptr ) );
    REQUIRE_NOTHROW( session->yield( "my payload.", [ ]( auto, auto )
    {
        return error_code( );
    } ) );
    REQUIRE_NOTHROW( session->yield( make_bytes( ), nullptr ) );
    REQUIRE_NOTHROW( session->yield( make_bytes( ), [ ]( auto, auto )
    {
        return error_code( );
    } ) );
    REQUIRE_NOTHROW( session->yield( make_bytes( "my payload." ), nullptr ) );
    REQUIRE_NOTHROW( session->yield( make_bytes( "my payload." ), [ ]( auto, auto )
    {
        return error_code( );
    } ) );
}
