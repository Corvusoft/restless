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
add_executable( session_close_integration_test_suite ${SOURCE_DIR}/session/close.cpp )
target_link_libraries( session_close_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_close_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_close_integration_test_suite )

add_executable( session_open_integration_test_suite ${SOURCE_DIR}/session/open.cpp )
target_link_libraries( session_open_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_open_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_open_integration_test_suite )

add_executable( session_send_integration_test_suite ${SOURCE_DIR}/session/send.cpp )
target_link_libraries( session_send_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_send_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_send_integration_test_suite )
