//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>
#include <corvusoft/stub/adaptor.hpp>
#include <corvusoft/stub/run_loop.hpp>

//System Namespaces
using std::error_code;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces
using corvusoft::stub::RunLoop;
using corvusoft::stub::Adaptor;
using corvusoft::core::make_bytes;

TEST_CASE( "Assert yield callback is invoked." )
{
    auto runloop = make_shared< RunLoop >( );
    auto adaptor = make_shared< Adaptor >( runloop );
    auto session = make_shared< Session >( adaptor, runloop );
    
    bool yield_called = false;
    REQUIRE_NOTHROW( session->yield( "data payload", [ &yield_called ] ( auto session, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( session not_eq nullptr );
        yield_called = true;
        return success;
    } ) );
    
    REQUIRE( yield_called );
    
    yield_called = false;
    REQUIRE_NOTHROW( session->yield( make_bytes( "data payload" ), [ &yield_called ] ( auto session, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( session not_eq nullptr );
        yield_called = true;
        return success;
    } ) );
    
    REQUIRE( yield_called );
}
