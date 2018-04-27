//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include <corvusoft/restless/session.hpp>
#include <corvusoft/restless/settings.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/stub/adaptor.hpp>
#include <corvusoft/stub/run_loop.hpp>

//System Namespaces
using std::error_code;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;
using corvusoft::restless::Settings;

//External Namespaces
using corvusoft::stub::RunLoop;
using corvusoft::stub::Adaptor;

TEST_CASE( "Assert open callback is invoked." )
{
    auto runloop = make_shared< RunLoop >( );
    auto adaptor = make_shared< Adaptor >( runloop );
    auto session = make_shared< Session >( adaptor, runloop );
    auto settings = make_shared< Settings >( );
    
    bool open_called = false;
    REQUIRE_NOTHROW( session->open( settings, [ &open_called ] ( auto session, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( session not_eq nullptr );
        open_called = true;
        return success;
    } ) );
    
    REQUIRE( open_called );
    
    open_called = false;
    REQUIRE_NOTHROW( session->open( "127.0.0.1", 80, [ &open_called ] ( auto session, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( session not_eq nullptr );
        open_called = true;
        return success;
    } ) );
    
    REQUIRE( open_called );
    
    open_called = false;
    REQUIRE_NOTHROW( session->open( nullptr, [ &open_called ] ( auto session, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( session not_eq nullptr );
        open_called = true;
        return success;
    } ) );
    
    REQUIRE( open_called );
}
