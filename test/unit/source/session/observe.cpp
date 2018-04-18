//System Includes
#include <chrono>
#include <memory>
#include <functional>
#include <system_error>

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::function;
using std::error_code;
using std::make_shared;
using std::chrono::milliseconds;

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces

TEST_CASE( "Assert invalid observe parameters." )
{
    auto session = make_shared< Session >( );
    REQUIRE_NOTHROW( session->observe( nullptr, nullptr, nullptr ) );
    REQUIRE_NOTHROW( session->observe( nullptr, nullptr, [ ]( auto, auto, auto )
    {
        return error_code( );
    } ) );
    REQUIRE_NOTHROW( session->observe( nullptr, [ ]( auto, auto )
    {
        return milliseconds::zero( );
    }, nullptr ) );
    REQUIRE_NOTHROW( session->observe( nullptr, [ ]( auto, auto )
    {
        return milliseconds::zero( );
    }, [ ]( auto, auto, auto )
    {
        return error_code( );
    } ) );
}
