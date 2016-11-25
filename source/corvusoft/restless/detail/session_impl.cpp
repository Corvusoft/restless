/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <regex>
#include <ciso646>
#include <sstream>
#include <utility>

//Project Includes
#include "corvusoft/restless/settings.hpp"
#include "corvusoft/restless/ssl_settings.hpp"
#include "corvusoft/restless/detail/session_impl.hpp"

//External Includes
#include <asio/read.hpp>
#include <asio/write.hpp>
#include <asio/connect.hpp>
#include <asio/read_until.hpp>
#include <corvusoft/restbed/string.hpp>

//System Namespaces
using std::stoi;
using std::stod;
using std::regex;
using std::string;
using std::size_t;
using std::smatch;
using std::multimap;
using std::function;
using std::to_string;
using std::make_pair;
using std::error_code;
using std::shared_ptr;
using std::make_shared;
using std::regex_match;
using std::stringstream;
using std::placeholders::_1;
using std::ostream_iterator;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

//Project Namespaces
using restless::detail::SessionImpl;

//External Namespaces
using restbed::String;
using asio::read;
using asio::write;
using asio::buffer;
using asio::ip::tcp;
using asio::streambuf;
using asio::read_until;
using asio::io_service;
using asio::steady_timer;

namespace restless
{
    namespace detail
    {
        SessionImpl::SessionImpl( const Uri& uri, const shared_ptr< const Settings >& settings ) : m_is_open( false ),
            m_uri( make_shared< Uri >( uri ) ),
            m_timeout( 0 ),
            m_buffer( make_shared< streambuf >( ) ),
            m_settings( settings ),
            m_io_service( make_shared< io_service >( ) ),
            m_timer( make_shared< steady_timer >( *m_io_service ) ),
            m_strand( make_shared< io_service::strand >( *m_io_service ) ),
            m_resolver( make_shared< tcp::resolver >( *m_io_service ) ),
            m_headers( ),
            m_socket( nullptr ),
#ifdef BUILD_SSL
            m_ssl_socket( nullptr )
#endif
        {
            if ( m_settings not_eq nullptr )
            {
                m_timeout = m_settings->get_connection_timeout( );
            }
        }
        
        SessionImpl::~SessionImpl( void )
        {
            return;
        }
        
        void SessionImpl::close( void )
        {
            m_is_open = false;
            
            if ( m_timer not_eq nullptr )
            {
                m_timer->cancel( );
            }
            
            if ( m_socket not_eq nullptr )
            {
                m_socket->close( );
            }
            
#ifdef BUILD_SSL
            
            if ( m_ssl_socket not_eq nullptr )
            {
                m_ssl_socket->lowest_layer( ).close( );
            }
            
#endif
        }
        
        void SessionImpl::socket_setup( void )
        {
            if ( m_socket == nullptr or m_is_open == false )
            {
#ifdef BUILD_SSL
            
                if ( String::uppercase( m_uri->get_scheme( ) ) == "HTTPS" )
                {
                    ssl_socket_setup( );
                }
                else
                {
#endif
                    m_socket = make_shared< tcp::socket >( *m_io_service );
#ifdef BUILD_SSL
                }
                
#endif
            }
        }
        
        void SessionImpl::timeout_setup( void )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( m_strand->wrap( bind( &SessionImpl::connection_timeout_handler, this, _1 ) ) );
        }
        
        void SessionImpl::timeout_teardown( void )
        {
            if ( m_timer not_eq nullptr )
            {
                m_timer->cancel( );
            }
        }
        
#ifdef BUILD_SSL
        void SessionImpl::ssl_socket_setup( void )
        {
            asio::ssl::context context( asio::ssl::context::sslv23 );
            
            if ( m_settings not_eq nullptr and m_settings->get_ssl_settings( ) not_eq nullptr )
            {
                const auto ssl_settings = m_settings->get_ssl_settings( );
                const auto pool = ssl_settings->get_certificate_authority_pool( );
                
                if ( pool.empty( ) )
                {
                    context.set_default_verify_paths( );
                }
                else
                {
                    context.add_verify_path( ssl_settings->get_certificate_authority_pool( ) );
                }
                
                m_ssl_socket = make_shared< asio::ssl::stream< asio::ip::tcp::socket > >( *m_io_service, context );
                m_ssl_socket->set_verify_mode( asio::ssl::verify_peer | asio::ssl::verify_fail_if_no_peer_cert );
            }
            else
            {
                m_ssl_socket = make_shared< asio::ssl::stream< asio::ip::tcp::socket > >( *m_io_service, context );
                m_ssl_socket->set_verify_mode( asio::ssl::verify_none );
            }
            
            m_ssl_socket->set_verify_callback( asio::ssl::rfc2818_verification( m_uri->get_authority( ) ) );
        }
#endif
        
        Bytes SessionImpl::fetch( const size_t length, const function< void ( const Bytes, const error_code ) >& completion_handler )
        {
            if ( length == 0 or
                    ( m_socket == nullptr
#ifdef BUILD_SSL
                      and m_ssl_socket == nullptr
#endif
                    ) )
            {
                return { };
            }
            
            Bytes data = { };
            
            if ( length > m_buffer->size( ) )
            {
                error_code error;
                const size_t size = length - m_buffer->size( );
#ifdef BUILD_SSL
                asio::read( *m_ssl_socket, *m_buffer, asio::transfer_at_least( size ), error );
#else
                asio::read( *m_socket, *m_buffer, asio::transfer_at_least( size ), error );
#endif
                
                if ( error and error not_eq asio::error::eof )
                {
                    return { };
                }
            }
            
            const auto data_ptr = asio::buffer_cast< const Byte* >( m_buffer->data( ) );
            data = Bytes( data_ptr, data_ptr + length );
            
            m_buffer->consume( length );
            
            return data;
        }
        
        Bytes SessionImpl::fetch( const string& delimiter, const function< void ( const Bytes, const error_code ) >& completion_handler )
        {
            return { };
        }
        
        shared_ptr< Response > SessionImpl::parse( const Bytes& data )
        {
            stringstream response_stream;
            copy( data.begin( ), data.end( ), ostream_iterator< char >( response_stream, "" ) );
            
            string status_line = String::empty;
            getline( response_stream, status_line );
            
            smatch matches;
            static const regex status_line_pattern( "^([a-zA-Z]+)\\/(\\d*\\.?\\d*) (-?\\d+) (.+)\\r$" );
            
            if ( not regex_match( status_line, matches, status_line_pattern ) or matches.size( ) not_eq 5 )
            {
                return create_error_response( String::format( "Error: HTTP response status line malformed '%s'", status_line.data( ) ) );
            }
            
            auto response = make_shared< Response >( );
            response->set_protocol( matches[ 1 ].str( ) );
            response->set_version( stod( matches[ 2 ].str( ) ) );
            response->set_status_code( stoi( matches[ 3 ].str( ) ) );
            response->set_status_message( matches[ 4 ].str( ) );
            
            string header = String::empty;
            multimap< string, string > headers = { };
            
            while ( getline( response_stream, header ) and header not_eq "\r" )
            {
                static const regex header_pattern( "^([^:.]*): *(.*)\\s*$" );
                smatch matches;
                
                if ( not regex_match( header, matches, header_pattern ) or matches.size( ) not_eq 3 )
                {
                    return create_error_response( String::format( "Error: Malformed HTTP response header '%s'", header.data( ) ) );
                }
                
                headers.insert( make_pair( matches[ 1 ], matches[ 2 ] ) );
            }
            
            response->set_headers( headers );
            
            return response;
        }
        
        Bytes SessionImpl::sync( const Bytes& data, const function< Bytes ( void ) >& upload_handler, error_code error )
        {
            socket_setup( );
            timeout_setup( );
            error = connect( );
            
            if ( error )
            {
                return { };
            }
            
            size_t length = 0;
            
#ifdef BUILD_SSL
            
            if ( m_socket not_eq nullptr )
            {
#endif
                asio::write( *m_socket, asio::buffer( data.data( ), data.size( ) ), error );
                
                if ( error )
                {
                    return { };
                }
                
                length = asio::read_until( *m_socket, *m_buffer, "\r\n\r\n", error );
                
                if ( error )
                {
                    return { };
                }
                
#ifdef BUILD_SSL
            }
            else
            {
                asio::write( *m_ssl_socket, asio::buffer( data.data( ), data.size( ) ), error );
                
                if ( error )
                {
                    return { };
                }
                
                length = asio::read_until( *m_ssl_socket, *m_buffer, "\r\n\r\n", error );
                
                if ( error )
                {
                    return { };
                }
            }
            
#endif
            timeout_teardown( );
            
            const auto response_ptr = asio::buffer_cast< const Byte* >( m_buffer->data( ) );
            auto buffer = Bytes( response_ptr, response_ptr + length );
            m_buffer->consume( length );
            
            return buffer;
        }
        
        void SessionImpl::async( const Bytes&, const function< Bytes ( void ) >& upload_handler, const function< void ( const shared_ptr< Session >, const shared_ptr< Request >, const shared_ptr< Response > ) >& response_handler )
        {
        
        }
        
        error_code SessionImpl::connect( const function< void ( const error_code& ) >& )
        {
#ifdef BUILD_SSL
            auto& socket = ( m_socket not_eq nullptr ) ? *m_socket : m_ssl_socket->lowest_layer( );
#else
            auto& socket = *m_socket;
#endif
            tcp::resolver::query query( m_uri->get_authority( ), ::to_string( m_uri->get_port( ) ) );
            
            error_code error;
            auto endpoint_iterator = m_resolver->resolve( query, error );
            
            if ( not error )
            {
                asio::connect( socket, endpoint_iterator, error );
            }
            
            return error;
        }
        
        void SessionImpl::connection_timeout_handler( const error_code& error )
        {
            if ( error )
            {
                return;
            }
            
            if ( m_timer->expires_at( ) > steady_clock::now( ) )
            {
                return;
            }
            
            close( );
        }
        
        shared_ptr< Response > SessionImpl::create_error_response( const string& message )
        {
            auto response = make_shared< Response >( );
            response->set_status_code( -1 );
            response->set_status_message( "Software Error" );
            response->set_body( message );
            response->set_header( "Content-Type", "text/plain" );
            response->set_header( "Content-Length", ::to_string( message.length( ) ) );
            
            return response;
        }
        
        shared_ptr< Response > SessionImpl::create_error_response( const error_code& error )
        {
            const auto body = String::format( "Error: %s", error.message( ).data( ) );
            return create_error_response( body );
        }
    }
}
