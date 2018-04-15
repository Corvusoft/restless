cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR )

project( "feature test suite" VERSION 2.0.0 LANGUAGES CXX )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( SYSTEM ${catch_INCLUDE} )

#
# Build
#
#add_executable( request_response_feature_test_suite ${SOURCE_DIR}/request_response.cpp )
#target_link_libraries( request_response_feature_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( request_response_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_response_feature_test_suite )
