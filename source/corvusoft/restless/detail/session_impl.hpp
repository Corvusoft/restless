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
#include <stdexcept>
#include <functional>
#include <system_error>

//Project Includes

//External Includes
#include <corvusoft/core/run_loop.hpp>
#include <corvusoft/core/log_level.hpp>
#include <corvusoft/network/tcpip.hpp>
#include <corvusoft/network/adaptor.hpp>
#include <corvusoft/protocol/frame.hpp>
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
                
                std::shared_ptr< protocol::HTTPFrameBuilder > builder = std::make_shared< protocol::HTTPFrameBuilder >( );
                
                std::multimap< std::string, std::string > default_headers { };
                
                std::multimap< std::string, const std::function< std::string ( void ) > > computed_headers { };
                
                std::function< std::error_code ( const int, const std::string ) > log_handler = nullptr;
                
                const std::shared_ptr< const Response > assemble( const core::Bytes data )
                {
                    auto frame = builder->assemble( data );
                    auto response = std::make_shared< Response >( );
                    
                    auto iterator = frame->meta.find( "protocol" );
                    if ( iterator not_eq frame->meta.end( ) )
                        response->set_protocol( core::make_string( iterator->second ) );
                    frame->meta.erase( "protocol" );
                    
                    try
                    {
                        iterator = frame->meta.find( "version" );
                        if ( iterator not_eq frame->meta.end( ) )
                            response->set_version( std::stod( core::make_string( iterator->second ) ) );
                        frame->meta.erase( "version" );
                        
                        iterator = frame->meta.find( "status" );
                        if ( iterator not_eq frame->meta.end( ) )
                            response->set_status_code( std::stoi( core::make_string( iterator->second ) ) );
                        frame->meta.erase( "status" );
                    }
                    catch ( const std::invalid_argument )
                    {
                        return nullptr;
                    }
                    catch ( const std::out_of_range )
                    {
                        return nullptr;
                    }
                    
                    iterator = frame->meta.find( "message" );
                    if ( iterator not_eq frame->meta.end( ) )
                        response->set_status_message( core::make_string( iterator->second ) );
                    frame->meta.erase( "message" );
                    
                    for ( auto header : frame->meta )
                        response->set_header( header.first, core::make_string( header.second ) );
                        
                    iterator = frame->data.find( "body" );
                    if ( iterator not_eq frame->data.end( ) )
                        response->set_body( iterator->second );
                }
                
                const core::Bytes disassemble( const std::shared_ptr< const Request > request )
                {
                    auto frame = std::make_shared< protocol::Frame >( );
                    frame->meta.emplace( "method", core::make_bytes( request->get_method( ) ) );
                    
                    auto parameters = request->get_query_parameters( );
                    auto path = ( parameters.empty( ) ) ? request->get_path( ) : request->get_path( ) + "?";
                    for ( auto parameter : parameters )
                        path += parameter.first + "=" + parameter.second + "&";
                    if ( not parameters.empty( ) ) path.pop_back( );
                    frame->meta.emplace( "path", core::make_bytes( path ) );
                    
                    //frame->meta.emplace( "protocol", core::make_bytes( request->get_protocol( ) ) );
                    frame->meta.emplace( "protocol", core::make_bytes( "HTTP" ) );
                    
                    // char* locale = strdup( std::setlocale( LC_NUMERIC, nullptr ) );
                    // std::setlocale( LC_NUMERIC, "C" );
                    // frame->meta.emplace( "version", core::make_bytes( std::to_string( request->get_version( ) ) ) );
                    frame->meta.emplace( "version", core::make_bytes( "1.1" ) );
                    // std::setlocale( LC_NUMERIC, locale );
                    // std::free( locale );
                    
                    for ( auto header : request->get_headers( ) )
                        frame->meta.emplace( header.first, core::make_bytes( header.second ) );
                        
                    frame->data.emplace( "body", request->get_body( ) );
                    
                    return builder->disassemble( frame );
                }
            };
        }
    }
}

#endif  /* _CORVUSOFT_RESTLESS_DETAIL_SESSION_IMPL_H */
