cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR )

project( "integration test suite" VERSION 2.0.0 LANGUAGES CXX )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( SYSTEM ${catch_INCLUDE} )

#
# Build
#
add_executable( response_accessors_integration_test_suite ${SOURCE_DIR}/response/accessors.cpp )
target_link_libraries( response_accessors_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( response_accessors_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_accessors_integration_test_suite )

add_executable( response_get_header_integration_test_suite ${SOURCE_DIR}/response/get_header.cpp )
target_link_libraries( response_get_header_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( response_get_header_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_get_header_integration_test_suite )

add_executable( response_get_headers_integration_test_suite ${SOURCE_DIR}/response/get_headers.cpp )
target_link_libraries( response_get_headers_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( response_get_headers_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_get_headers_integration_test_suite )

add_executable( response_has_header_integration_test_suite ${SOURCE_DIR}/response/has_header.cpp )
target_link_libraries( response_has_header_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( response_has_header_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_has_header_integration_test_suite )

add_executable( session_accessors_integration_test_suite ${SOURCE_DIR}/session/accessors.cpp )
target_link_libraries( session_accessors_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_accessors_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_accessors_integration_test_suite )

add_executable( session_close_integration_test_suite ${SOURCE_DIR}/session/close.cpp )
target_link_libraries( session_close_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_close_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_close_integration_test_suite )

add_executable( session_fetch_integration_test_suite ${SOURCE_DIR}/session/fetch.cpp )
target_link_libraries( session_fetch_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_fetch_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_fetch_integration_test_suite )

add_executable( session_observe_integration_test_suite ${SOURCE_DIR}/session/observe.cpp )
target_link_libraries( session_observe_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_observe_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_observe_integration_test_suite )

add_executable( session_open_integration_test_suite ${SOURCE_DIR}/session/open.cpp )
target_link_libraries( session_open_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_open_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_open_integration_test_suite )

add_executable( session_send_integration_test_suite ${SOURCE_DIR}/session/send.cpp )
target_link_libraries( session_send_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_send_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_send_integration_test_suite )

add_executable( session_yield_integration_test_suite ${SOURCE_DIR}/session/yield.cpp )
target_link_libraries( session_yield_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_yield_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_yield_integration_test_suite )

add_executable( settings_accessors_integration_test_suite ${SOURCE_DIR}/settings/accessors.cpp )
target_link_libraries( settings_accessors_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( settings_accessors_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/settings_accessors_integration_test_suite )
