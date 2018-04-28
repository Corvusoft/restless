//System Includes
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
using std::shared_ptr;
using std::error_code;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;
using corvusoft::restless::Request;
using corvusoft::restless::Response;

//External Namespaces
using corvusoft::stub::RunLoop;
using corvusoft::stub::Adaptor;
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Request/Response lifecycle." )
{
    auto runloop = make_shared< RunLoop >( );
    auto adaptor = make_shared< Adaptor >( runloop );
    adaptor->set_data( make_bytes( "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nabcde" ) );
    
    bool response_recieved = false;
    auto session = make_shared< Session >( adaptor, runloop );
    session->open( "www.corvusoft.com.au", 80, [ &response_recieved ]( auto session, auto status )
    {
        REQUIRE( session not_eq nullptr );
        REQUIRE( status == error_code( ) );
        
        auto request = make_shared< Request >( );
        request->set_version( 1.1 );
        request->set_path( "/api" );
        request->set_method( "GET" );
        request->set_protocol( "HTTP" );
        
        session->send( request, [ &response_recieved ] ( auto session, auto response, auto status )
        {
            REQUIRE( session not_eq nullptr );
            REQUIRE( response not_eq nullptr );
            REQUIRE( status == error_code( ) );
            REQUIRE( response->get_protocol( ) == "HTTP" );
            REQUIRE( response->get_status_code( ) == 200 );
            REQUIRE( response->get_status_message( ) == "OK" );
            REQUIRE( response->get_body( ) == make_bytes( "abcde" ) );
            REQUIRE( response->get_header( "Content-Length", 0 ) == 5 );
            
            response_recieved = true;
            return error_code( );
        } );
        
        return error_code( );
    } );
    
    REQUIRE( response_recieved );
}
