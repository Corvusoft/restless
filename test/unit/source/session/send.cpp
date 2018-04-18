//System Includes
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

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces

TEST_CASE( "Assert invalid send parameters." )
{
    auto session = make_shared< Session >( );
    REQUIRE_NOTHROW( session->send( nullptr, nullptr ) );
    REQUIRE_NOTHROW( session->send( nullptr, [ ]( auto, auto, auto )
    {
        return error_code( );
    } ) );
}
