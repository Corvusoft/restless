//System Includes
#include <chrono>
#include <memory>
#include <system_error>

//Project Includes
#include <corvusoft/restless/session.hpp>
#include <corvusoft/restless/request.hpp>
#include <corvusoft/restless/response.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>
#include <corvusoft/stub/adaptor.hpp>
#include <corvusoft/stub/run_loop.hpp>

//System Namespaces
using std::error_code;
using std::make_shared;
using std::chrono::milliseconds;

//Project Namespaces
using corvusoft::restless::Session;
using corvusoft::restless::Request;
using corvusoft::restless::Response;

//External Namespaces
using corvusoft::stub::RunLoop;
using corvusoft::stub::Adaptor;
using corvusoft::core::make_bytes;

TEST_CASE( "Assert observe callback is invoked." )
{
    auto runloop = make_shared< RunLoop >( );
    auto adaptor = make_shared< Adaptor >( runloop );
    adaptor->set_data( make_bytes( "HTTP/1.1 200 OK\r\n\r\n" ) );
    auto session = make_shared< Session >( adaptor, runloop );
    
    bool event_handler_called = false;
    bool reaction_handler_called = false;
    auto request = make_shared< Request >( );
    REQUIRE_NOTHROW( session->observe( request, [ &event_handler_called ]( auto response, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( response not_eq nullptr );
        REQUIRE( response->get_status_code( ) == 200 );
        event_handler_called = true;
        return milliseconds::zero( );
    },
    [ &reaction_handler_called ] ( auto session, auto response, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( session not_eq nullptr );
        REQUIRE( response not_eq nullptr );
        REQUIRE( response->get_status_code( ) == 200 );
        reaction_handler_called = true;
        return success;
    } ) );
    
    REQUIRE( event_handler_called );
    REQUIRE( reaction_handler_called );
}
