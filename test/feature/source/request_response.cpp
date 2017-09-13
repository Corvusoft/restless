//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include <corvusoft/restless/session.hpp>
#include <corvusoft/restless/request.hpp>
#include <corvusoft/restless/response.hpp>
#include <corvusoft/restless/settings.hpp>

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
using corvusoft::restless::Settings;

//External Namespaces

TEST_CASE( "Complete request-response cycle." )
{
    auto settings = make_shared< Settings >( );
    
    auto request = make_shared< Request >( );
    request->set_method( "GET" );
    
    auto session = make_shared< Session >( );
    session->open( "178.62.20.193", 80 ); //add open_handler( session );
    
    //session->send( request,
    //    const function< error_code ( const shared_ptr< const Response > ) > response_handler,
    //    const function< error_code ( const shared_ptr< Request >, const shared_ptr< Adaptor > ) > upload_handler,
    //    const function< error_code ( const shared_ptr< Response >, const shared_ptr< Adaptor > ) > download_handler )
    
    
    // auto adaptor = MockAdaptor::create( );
    // adaptor->set_response( response );
    // adaptor->set_open_port_expectation( "111.222.333.444" );
    // adaptor->set_open_address_expectation( "111.222.333.444" );
    
    // auto session = make_shared< Session >( );
    // session->set_network( adaptor );
    
    // auto error = session->open( "111.222.333.444", 8090 );
    // if ( error ) ASSERTFAIL;
    
    // error = session->send( request, response_handler );
    // if ( error ) ASSERTFAIL;
    
    // runloop->wait( );
}
