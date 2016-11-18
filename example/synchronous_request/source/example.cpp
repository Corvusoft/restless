/*
 * Example illustrating a synchronous HTTP request.
 *
 * Usage:
 *    ./distribution/example/synchronous_request
 */

#include <memory>
#include <cstdio>
#include <cstdlib>
#include <restless>

using namespace std;
using namespace restless;

void print( const shared_ptr< Response >& response )
{
    fprintf( stderr, "Status Code:    %i\n", response->get_status_code( ) );
    fprintf( stderr, "Status Message: %s\n", response->get_status_message( ).data( ) );
    fprintf( stderr, "HTTP Version:   %.1f\n", response->get_version( ) );
    fprintf( stderr, "HTTP Protocol:  %s\n", response->get_protocol( ).data( ) );
    
    for ( const auto header : response->get_headers( ) )
    {
        fprintf( stderr, "Header '%s' > '%s'\n", header.first.data( ), header.second.data( ) );
    }
    
    fprintf( stderr, "Body:\n%.*s\n", ( int ) response->get_body( ).size( ), response->get_body( ).data( ) );
}

int main( const int, const char** )
{
    auto session = make_shared< Session >( Uri( "http://www.corvusoft.co.uk" ) );
    
    auto request = make_shared< Request >( );
    request->set_path( "/" );
    request->set_header( "Accept", "*/*" );
    request->set_header( "Host", "corvusoft.co.uk" );
    request->set_query_parameter( "query", "search term" );
    
    auto response = session->send( request );
    
    if ( response->get_status_code( ) not_eq - 1 )
    {
        const auto length = response->get_header( "Content-Length", 0 );
        const auto body = session->fetch( length );
        response->set_body( body );
    }
    
    print( response );
    
    return EXIT_SUCCESS;
}
