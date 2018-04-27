//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include <corvusoft/restless/request.hpp>
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
using corvusoft::restless::Request;
using corvusoft::restless::Session;

//External Namespaces
using corvusoft::stub::RunLoop;
using corvusoft::stub::Adaptor;
using corvusoft::core::make_bytes;

TEST_CASE( "Assert send callback is invoked." )
{
    auto runloop = make_shared< RunLoop >( );
    auto adaptor = make_shared< Adaptor >( runloop );
    adaptor->set_data( make_bytes( "HTTP/1.1 200 OK\r\n\r\n" ) );
    auto session = make_shared< Session >( adaptor, runloop );
    
    bool send_called = false;
    auto request = make_shared< Request >( );
    REQUIRE_NOTHROW( session->send( request, [ &send_called ] ( auto session, auto response, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( session not_eq nullptr );
        REQUIRE( response not_eq nullptr );
        send_called = true;
        return success;
    } ) );
    
    REQUIRE( send_called );
    
    send_called = false;
    REQUIRE_NOTHROW( session->send( nullptr, [ &send_called ] ( auto session, auto response, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( session not_eq nullptr );
        REQUIRE( response not_eq nullptr );
        send_called = true;
        return success;
    } ) );
    
    REQUIRE( send_called == false );
}
