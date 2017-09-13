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
#include <corvusoft/core/run_loop.hpp>
#include <corvusoft/network/tcpip_adaptor.hpp>
#include <corvusoft/protocol/http.hpp>

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
using corvusoft::core::RunLoop;
using corvusoft::protocol::HTTP;
using corvusoft::network::TCPIPAdaptor;

TEST_CASE( "Modify session instance." )
{
    const auto session = make_shared< Session >( );
    session->set_settings( make_shared< Settings >( ) );
    REQUIRE( session->get_settings( ) not_eq nullptr );
    
    session->set_runloop( make_shared< RunLoop >( ) );
    REQUIRE( session->get_runloop( ) not_eq nullptr );
    
    session->set_adaptor( TCPIPAdaptor::create( ) );
    REQUIRE( session->get_adaptor( ) not_eq nullptr );
    
    session->set_protocol( make_shared< HTTP >( ) );
    REQUIRE( session->get_protocol( ) not_eq nullptr );
    
    session->set_connection_timeout_handler( [ ]( const std::shared_ptr< const Request > )
    {
        return error_code( );
    } );
    REQUIRE( session->get_connection_timeout_handler( ) not_eq nullptr );
    
    session->set_error_handler( [ ]( const std::shared_ptr< const Request >, const std::shared_ptr< const Response >, const std::error_code )
    {
        return error_code( );
    } );
    REQUIRE( session->get_error_handler( ) not_eq nullptr );
}
