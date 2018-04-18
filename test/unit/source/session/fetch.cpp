//System Includes
#include <memory>
#include <functional>
#include <system_error>

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::function;
using std::error_code;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces
using corvusoft::core::make_bytes;

TEST_CASE( "Assert invalid fetch parameters." )
{
    auto session = make_shared< Session >( );
    //REQUIRE_NOTHROW( session->fetch( -23, nullptr ) );
    //REQUIRE_NOTHROW( session->fetch( 0, nullptr ) );
    //REQUIRE_NOTHROW( session->fetch( 34463, nullptr ) );
    //REQUIRE_NOTHROW( session->fetch( -34, [ ]( auto, auto, auto ) { return error_code( ); } ) );
    //REQUIRE_NOTHROW( session->fetch( 0, [ ]( auto, auto, auto ) { return error_code( ); } ) );
    //REQUIRE_NOTHROW( session->fetch( 34463, [ ]( auto, auto, auto ) { return error_code( ); } ) );
    REQUIRE_NOTHROW( session->fetch( "", nullptr ) );
    REQUIRE_NOTHROW( session->fetch( "\r\n", nullptr ) );
    REQUIRE_NOTHROW( session->fetch( "", [ ]( auto, auto, auto )
    {
        return error_code( );
    } ) );
    REQUIRE_NOTHROW( session->fetch( "\r\n", [ ]( auto, auto, auto )
    {
        return error_code( );
    } ) );
    REQUIRE_NOTHROW( session->fetch( make_bytes( ), nullptr ) );
    REQUIRE_NOTHROW( session->fetch( make_bytes( "\r\n" ), nullptr ) );
    REQUIRE_NOTHROW( session->fetch( make_bytes( ), [ ]( auto, auto, auto )
    {
        return error_code( );
    } ) );
    REQUIRE_NOTHROW( session->fetch( make_bytes( "\r\n" ), [ ]( auto, auto, auto )
    {
        return error_code( );
    } ) );
}
