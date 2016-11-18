/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTLESS_DETAIL_SESSION_IMPL_H
#define _RESTLESS_DETAIL_SESSION_IMPL_H 1

//System Includes
#include <string>
#include <chrono>
#include <memory>
#include <cstddef>
#include <functional>
#include <system_error>

//Project Includes
#include "corvusoft/restless/uri.hpp"
#include "corvusoft/restless/byte.hpp"
#include "corvusoft/restless/request.hpp"
#include "corvusoft/restless/response.hpp"

//External Includes
#include <asio/ip/tcp.hpp>
#include <asio/streambuf.hpp>
#include <asio/steady_timer.hpp>
#include <asio/io_service.hpp>
#include <asio/io_service_strand.hpp>

#ifdef BUILD_SSL
    #include <asio/ssl.hpp>
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restless
{
    //Forward Declarations
    class Session;
    class Settings;
    
    namespace detail
    {
        //Forward Declarations
        
        class SessionImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                SessionImpl( const Uri& uri, const std::shared_ptr< const Settings >& settings );
                
                virtual ~SessionImpl( void );
                
                //Functionality
                void close( void );
                
                void socket_setup( void );
                
                void timeout_setup( void );
                
                void timeout_teardown( void );
#ifdef BUILD_SSL
                void ssl_socket_setup( void );
#endif
                Bytes fetch( const std::size_t length );
                
                Bytes fetch( const std::string& delimiter );
                
                std::shared_ptr< Response > parse( const Bytes& response );
                
                Bytes sync( const Bytes& data, std::error_code error );
                
                void async( const Bytes& data, const std::function< void ( const std::error_code&, size_t ) >& callback );
                
                std::error_code connect( const std::function< void ( const std::error_code& ) >& callback = nullptr );
                
                void connection_timeout_handler( const std::error_code& error );
                
                std::shared_ptr< Response > create_error_response( const std::string& message );
                
                std::shared_ptr< Response > create_error_response( const std::error_code& error );
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                bool m_is_open;
                
                std::shared_ptr< Uri > m_uri;
                
                std::chrono::milliseconds m_timeout;
                
                std::shared_ptr< asio::streambuf > m_buffer;
                
                std::shared_ptr< const Settings > m_settings;
                
                std::shared_ptr< asio::io_service > m_io_service;
                
                std::shared_ptr< asio::steady_timer > m_timer;
                
                std::shared_ptr< asio::io_service::strand > m_strand;
                
                std::shared_ptr< asio::ip::tcp::resolver > m_resolver;
                
                std::multimap< std::string, std::string > m_headers;
                
                std::shared_ptr< asio::ip::tcp::socket > m_socket;
                
                std::shared_ptr< asio::ssl::stream< asio::ip::tcp::socket > > m_ssl_socket;
                
            protected:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            private:
                //Friends
                
                //Definitions
                
                //Constructors
                SessionImpl( const SessionImpl& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                SessionImpl& operator =( const SessionImpl& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _RESTLESS_DETAIL_SESSION_IMPL_H */
