//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include <corvusoft/restless/session.hpp>
#include <corvusoft/restless/request.hpp>
#include <corvusoft/restless/response.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::shared_ptr;
using std::error_code;
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;
using corvusoft::restless::Request;
using corvusoft::restless::Response;

//External Namespaces

#include <thread>

TEST_CASE( "Request/Response cycle." )
{
    auto session = make_shared< Session >( );
    session->open( "www.google.com.au", 80, [ ]( auto session, auto status )
    {
        fprintf( stderr, "Open called.\n" );
        
        REQUIRE( status == error_code( ) );
        REQUIRE( session not_eq nullptr );
        
        auto request = make_shared< Request >( );
        request->set_method( "GET" );
        request->set_path( "/" );
        request->set_protocol( "HTTP" );
        request->set_version( 1.1 );
        
        session->send( request, [ ] ( auto session, auto response, auto status )
        {
            fprintf( stderr, "Send called.\n" );
            
            REQUIRE( status == error_code( ) );
            REQUIRE( session not_eq nullptr );
            REQUIRE( response not_eq nullptr );
            
            REQUIRE( response->get_status_code( ) == 200 );
            
            //fprintf( stderr, "Response: %.*s\n", response->get_body( ).size( ), response->get_body( ).data( ) );
            return error_code( );
        } );
        
        return error_code( );
    } );
    
    std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
    
    session->close( [ ]( auto session, auto status )
    {
        fprintf( stderr, "Closed called.\n" );
        return error_code( );
    } );
    
    std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
}
