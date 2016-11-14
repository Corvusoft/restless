# Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.

project( "example" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/example" )

#
# Build
#
add_executable( synchronous_request synchronous_request/source/example.cpp )
target_link_libraries( synchronous_request ${CMAKE_PROJECT_NAME} )

add_executable( asynchronous_request asynchronous_request/source/example.cpp )
target_link_libraries( asynchronous_request ${CMAKE_PROJECT_NAME} )

#
# Install
#
if ( NOT DEFINED CMAKE_INSTALL_LIBDIR )
    set( EXAMPLE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
    set( RESOURCE_INSTALL_DIR "${EXAMPLE_INSTALL_DIR}/resource" )
else ( )
    set( EXAMPLE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/restbed" )
    set( RESOURCE_INSTALL_DIR "${EXAMPLE_INSTALL_DIR}/${PROJECT_NAME}/resource" )
endif ( )

install( DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/example" DESTINATION ${EXAMPLE_INSTALL_DIR} FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE )
