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
add_executable( session_integration_test_suite ${SOURCE_DIR}/session.cpp )
target_link_libraries( session_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_integration_test_suite )
