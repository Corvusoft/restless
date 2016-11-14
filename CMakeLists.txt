# Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.

cmake_minimum_required( VERSION 2.8.10 )

project( "restless" )
set( restless_VERSION_MAJOR 0 )
set( restless_VERSION_MINOR 0.0 )
set( restless_VERSION ${restless_VERSION_MAJOR}.${restless_VERSION_MINOR} )
set( PACKAGE_VERSION ${restless_VERSION} )
set( VERSION "${restless_VERSION}" )

#
# Build Options
#
option( BUILD_SHARED   "Build shared library."              OFF )
option( BUILD_EXAMPLES "Build examples applications."       OFF )
option( BUILD_TESTS    "Build all available test suites."   OFF )
option( BUILD_SSL      "Build secure socket layer support."  ON )

#
# Configuration
#
include( "${CMAKE_SOURCE_DIR}/cmake/configuration.cmake" )

message( "   ${Blue}Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.${Reset}" )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules" )

find_package( asio REQUIRED )
find_package( restbed REQUIRED )
include_directories( SYSTEM ${asio_INCLUDE} ${restbed_INCLUDE} )

if ( BUILD_SSL )
    find_package( openssl REQUIRED )
    include_directories( SYSTEM ${ssl_INCLUDE} )
endif ( )

#
# Build
#
include( "${CMAKE_SOURCE_DIR}/cmake/manifest.cmake" )

include_directories( ${INCLUDE_DIR} )

add_library( ${PROJECT_NAME} ${MANIFEST} $<TARGET_OBJECTS:restbed> )

if ( BUILD_SHARED )
    set_target_properties( ${PROJECT_NAME} PROPERTIES SOVERSION ${restless_VERSION_MAJOR} VERSION ${restless_VERSION} )
endif ( )

if ( BUILD_SSL )
    target_link_libraries( ${PROJECT_NAME} LINK_PRIVATE ${ssl_LIBRARY} ${crypto_LIBRARY} )
else ( )
    target_link_libraries( ${PROJECT_NAME} )
endif ( )

if ( BUILD_EXAMPLES )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/example" )
endif ( )

if ( BUILD_TESTS )
    find_package( catch REQUIRED )

    enable_testing( )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/test/unit" )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/test/acceptance" )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/test/regression" )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/test/integration" )
endif ( )

#
# Install
#
include( "${CMAKE_SOURCE_DIR}/cmake/artifacts.cmake" )

if ( NOT DEFINED CMAKE_INSTALL_LIBDIR )
    set( CMAKE_INSTALL_LIBDIR library )
endif ( )

install( FILES "${INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION "${CMAKE_INSTALL_PREFIX}/include" )
install( FILES ${ARTIFACTS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/corvusoft/${PROJECT_NAME}" )
install( TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library )
