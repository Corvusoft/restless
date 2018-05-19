//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::error_code;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces

TEST_CASE( "Assert invalid close parameter." )
{
    auto session = make_shared< Session >( );
    REQUIRE_NOTHROW( session->close( nullptr ) );
    REQUIRE_NOTHROW( session->close( [ ] ( auto, auto )
    {
        return error_code( );
    } ) );
}
