//System Includes
#include <memory>
#include <cstdint>
#include <system_error>

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>
#include <corvusoft/stub/adaptor.hpp>
#include <corvusoft/stub/run_loop.hpp>

//System Namespaces
using std::size_t;
using std::error_code;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces
using corvusoft::stub::RunLoop;
using corvusoft::stub::Adaptor;
using corvusoft::core::make_bytes;

TEST_CASE( "Assert fetch callback is invoked and correct data supplied via length parameter." )
{
    auto runloop = make_shared< RunLoop >( );
    auto adaptor = make_shared< Adaptor >( runloop );
    adaptor->set_data( make_bytes( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ) );
    auto session = make_shared< Session >( adaptor, runloop );
    
    bool fetch_called = false;
    REQUIRE_NOTHROW( session->fetch( 5, [ &fetch_called ] ( auto session, auto data, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( data.size( ) == 5 );
        REQUIRE( data == make_bytes( "ABCDE" ) );
        REQUIRE( session not_eq nullptr );
        fetch_called = true;
        return success;
    } ) );
    
    REQUIRE( fetch_called );
    
    fetch_called = false;
    REQUIRE_NOTHROW( session->fetch( 10, [ &fetch_called ] ( auto session, auto data, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( data.size( ) == 10 );
        REQUIRE( data == make_bytes( "FGHIJKLMNO" ) );
        REQUIRE( session not_eq nullptr );
        fetch_called = true;
        return success;
    } ) );
    
    REQUIRE( fetch_called );
}

TEST_CASE( "Assert fetch callback is invoked and correct data supplied via delimiter parameter." )
{
    auto runloop = make_shared< RunLoop >( );
    auto adaptor = make_shared< Adaptor >( runloop );
    adaptor->set_data( make_bytes( "Software Engineering might be science; but that's not what I do. I'm a hacker, not an engineer." ) );
    auto session = make_shared< Session >( adaptor, runloop );
    
    bool fetch_called = false;
    REQUIRE_NOTHROW( session->fetch( " ", [ &fetch_called ] ( auto session, auto data, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( data.size( ) == 8 );
        REQUIRE( data == make_bytes( "Software" ) );
        REQUIRE( session not_eq nullptr );
        fetch_called = true;
        return success;
    } ) );
    
    REQUIRE( fetch_called );
    
    fetch_called = false;
    REQUIRE_NOTHROW( session->fetch( make_bytes( " " ), [ &fetch_called ] ( auto session, auto data, auto error )
    {
        error_code success;
        REQUIRE( error == success );
        REQUIRE( data.size( ) == 11 );
        REQUIRE( data == make_bytes( "Engineering" ) );
        REQUIRE( session not_eq nullptr );
        fetch_called = true;
        return success;
    } ) );
    
    REQUIRE( fetch_called );
}
