//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>
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

TEST_CASE( "Assert close callback is invoked." )
{
    auto runloop = make_shared< RunLoop >( );
    auto adaptor = make_shared< Adaptor >( runloop );
    auto session = make_shared< Session >( adaptor, runloop );
    
    bool close_called = false;
    REQUIRE_NOTHROW( session->close( [ &close_called ] ( auto adaptor, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( adaptor not_eq nullptr );
        close_called = true;
        return success;
    } ) );
    
    REQUIRE( close_called );
}
