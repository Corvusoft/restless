cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR )

project( "unit test suite" VERSION 2.0.0 LANGUAGES CXX )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( SYSTEM ${catch_INCLUDE} )

#
# Build
#
add_executable( request_unit_test_suite ${SOURCE_DIR}/request.cpp )
target_link_libraries( request_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( request_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_unit_test_suite )

add_executable( response_unit_test_suite ${SOURCE_DIR}/response.cpp )
target_link_libraries( response_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( response_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_unit_test_suite )

add_executable( session_unit_test_suite ${SOURCE_DIR}/session.cpp )
target_link_libraries( session_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_unit_test_suite )

add_executable( settings_unit_test_suite ${SOURCE_DIR}/settings.cpp )
target_link_libraries( settings_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( settings_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/settings_unit_test_suite )

add_executable( status_unit_test_suite ${SOURCE_DIR}/status.cpp )
target_link_libraries( status_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( status_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/status_unit_test_suite )
