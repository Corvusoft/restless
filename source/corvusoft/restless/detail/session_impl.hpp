/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTLESS_DETAIL_SESSION_IMPL_H
#define _CORVUSOFT_RESTLESS_DETAIL_SESSION_IMPL_H 1

//System Includes
#include <map>
#include <memory>
#include <string>
#include <clocale>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <functional>
#include <system_error>

//Project Includes

//External Includes
#include <corvusoft/core/run_loop.hpp>
#include <corvusoft/core/log_level.hpp>
#include <corvusoft/network/tcpip.hpp>
#include <corvusoft/protocol/http_frame.hpp>
#include <corvusoft/protocol/http_frame_builder.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    
    namespace restless
    {
        //Forward Declarations
        class Settings;
        
        namespace detail
        {
            //Forward Declarations
            
            struct SessionImpl
            {
                std::shared_ptr< Settings > settings = nullptr;
                
                std::shared_ptr< core::RunLoop > runloop = nullptr;
                
                std::shared_ptr< network::Adaptor > adaptor = nullptr;
                
                std::multimap< std::string, std::string > default_headers { };
                
                std::multimap< std::string, const std::function< std::string ( void ) > > computed_headers { };
                
                std::function< std::error_code ( const int, const std::string ) > log_handler = nullptr;
                
                const std::shared_ptr< const Response > assemble( std::shared_ptr< protocol::Frame > value )
                {
                    auto frame = std::dynamic_pointer_cast< protocol::HTTPFrame >( value );
                    if ( frame == nullptr ) return nullptr;
                    
                    auto response = std::make_shared< Response >( );
                    response->set_body( frame->get_body( ) );
                    response->set_version( parse_version( frame->get_version( ) ) );
                    response->set_protocol( core::make_string( frame->get_protocol( ) ) );
                    response->set_status_code( parse_status_code( frame->get_status_code( ) ) );
                    response->set_status_message( core::make_string( frame->get_status_message( ) ) );
                    
                    for ( auto header : frame->get_headers( ) )
                        response->set_header( header.first, core::make_string( header.second ) );
                        
                    return response;
                }
                
                const core::Bytes disassemble( const std::shared_ptr< const Request > request )
                {
                    auto frame = std::make_shared< protocol::HTTPFrame >( );
                    frame->set_path( compose_path( request ) );
                    frame->set_method( request->get_method( ) );
                    frame->set_protocol( request->get_protocol( ) );
                    frame->set_version( compose_version( request->get_version( ) ) );
                    
                    for ( auto header : request->get_headers( ) )
                        frame->set_header( header.first, header.second );
                        
                    frame->set_body( request->get_body( ) );
                    
                    auto builder = std::make_shared< protocol::HTTPFrameBuilder >( );
                    return builder->disassemble( frame );
                }
                
                double parse_version( const core::Bytes& value )
                try
                {
                    return std::stod( core::make_string( value ) );
                }
                catch ( const std::invalid_argument )
                {
                    return 0;
                }
                catch ( const std::out_of_range )
                {
                    return 0;
                }
                
                int parse_status_code( const core::Bytes& value )
                try
                {
                    fprintf( stderr, "status code '%.*s'\n", value.size( ), value.data() );
                    return std::stoi( core::make_string( value ) );
                }
                catch ( const std::invalid_argument )
                {
                    return 0;
                }
                catch ( const std::out_of_range )
                {
                    return 0;
                }
                
                std::string compose_path( const std::shared_ptr< const Request > request )
                {
                    auto parameters = request->get_query_parameters( );
                    if ( parameters.empty( ) ) return request->get_path( );
                    
                    auto path = request->get_path( ) + "?";
                    for ( auto parameter : parameters )
                        path += parameter.first + "=" + parameter.second + "&";
                        
                    path.pop_back( );
                    return path;
                }
                
                std::string compose_version( const double value )
                {
                    auto locale = setlocale( LC_NUMERIC, nullptr );
                    setlocale( LC_NUMERIC, "C" );
                    
                    std::ostringstream stream;
                    stream << std::setprecision( 2 ) << value;
                    auto version = stream.str( );
                    
                    setlocale( LC_NUMERIC, locale );
                    return version;
                }
            };
        }
    }
}

#endif  /* _CORVUSOFT_RESTLESS_DETAIL_SESSION_IMPL_H */
