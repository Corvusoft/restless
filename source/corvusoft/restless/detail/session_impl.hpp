/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <memory>
#include <string>
#include <clocale>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <system_error>

//Project Includes

//External Includes
#include <corvusoft/core/run_loop.hpp>
#include <corvusoft/core/log_level.hpp>
#include <corvusoft/network/adaptor.hpp>
#include <corvusoft/network/uri_builder.hpp>
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
        class Session;
        class Response;
        class Settings;
        
        namespace detail
        {
            //Forward Declarations
            
            struct SessionImpl
            {
                core::Bytes buffer { };
                
                std::shared_ptr< Settings > settings = nullptr;
                
                std::shared_ptr< core::RunLoop > runloop = nullptr;
                
                std::shared_ptr< network::Adaptor > adaptor = nullptr;
                
                std::multimap< std::string, std::string > default_headers { };
                
                std::multimap< std::string, const std::function< std::string ( void ) > > computed_headers { };
                
                void receive( const std::shared_ptr< Session > session, const std::function< std::error_code ( const std::shared_ptr< Session >, const std::shared_ptr< const Response >, const std::error_code ) > completion_handler )
                {
                    if ( completion_handler == nullptr ) return;
                    
                    auto builder = std::make_shared< protocol::HTTPFrameBuilder >( );
                    adaptor->consume( [ this, session, completion_handler, builder ]( auto, auto data, auto status )
                    {
                        if ( status ) return completion_handler( session, nullptr, status );
                        buffer.insert( std::end( buffer ), std::begin( data ), std::end( data ) );
                        
                        auto frame = builder->assemble( buffer );
                        if ( not builder->is_finalised( ) )
                            return make_error_code( std::errc::resource_unavailable_try_again ); //add circuit breaker.
                            
                        auto response = assemble( frame );
                        if ( response == nullptr )
                            return completion_handler( session, nullptr, make_error_code( std::errc::bad_message ) );
                            
                        auto body = response->get_body( );
                        auto position = std::search( std::begin( buffer ), std::end( buffer ), std::begin( body ), std::end( body ) );
                        if ( body.empty( ) or position == std::end( buffer ) )
                            buffer.clear( );
                        else
                            buffer.erase( std::begin( buffer ), position + body.size( ) );
                            
                        return completion_handler( session, response, status );
                    } );
                }
                
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
                    auto builder = std::make_shared< network::URIBuilder >( );
                    builder->set_path( request->get_path( ) );
                    builder->set_parameters( request->get_query_parameters( ) );
                    return builder->build( );
                }
                
                std::string compose_version( const double value  )
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
