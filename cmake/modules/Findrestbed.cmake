# Copyright 2014-2016, Corvusoft Ltd, All Rights Reserved.

find_path( restbed_PROJECT CMakeLists.txt HINTS "${CMAKE_SOURCE_DIR}/dependency/restbed" )

if ( restbed_PROJECT )
    set( restbed_FOUND TRUE )

    include_directories( "${restbed_PROJECT}/source" )

    add_library( restbed OBJECT
        ${restbed_PROJECT}/source/corvusoft/restbed/byte.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/common.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/uri.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/uri.cpp
        ${restbed_PROJECT}/source/corvusoft/restbed/detail/uri_impl.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/string.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/string.cpp
        ${restbed_PROJECT}/source/corvusoft/restbed/request.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/request.cpp
        ${restbed_PROJECT}/source/corvusoft/restbed/detail/request_impl.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/response.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/response.cpp
        ${restbed_PROJECT}/source/corvusoft/restbed/detail/response_impl.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/settings.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/settings.cpp
        ${restbed_PROJECT}/source/corvusoft/restbed/detail/settings_impl.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/ssl_settings.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/ssl_settings.cpp
        ${restbed_PROJECT}/source/corvusoft/restbed/detail/ssl_settings_impl.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/detail/socket_impl.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/detail/socket_impl.cpp
     )

     set( RESTBED_ARTIFACTS
        ${restbed_PROJECT}/source/corvusoft/restbed/uri.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/byte.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/common.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/string.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/request.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/settings.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/response.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/status_code.hpp
        ${restbed_PROJECT}/source/corvusoft/restbed/ssl_settings.hpp
    )

    install( FILES ${RESTBED_ARTIFACTS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/corvusoft/restbed" )

    message( STATUS "${Green}Found Restbed include at: ${restbed_PROJECT}${Reset}" )
else ( )
    message( FATAL_ERROR "${Red}Failed to locate Restbed dependency.${Reset}" )
endif ( )
