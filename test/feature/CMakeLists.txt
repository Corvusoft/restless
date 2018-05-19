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
add_executable( http_pipelining_feature_test_suite ${SOURCE_DIR}/http_pipelining.cpp )
target_link_libraries( http_pipelining_feature_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_pipelining_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_pipelining_feature_test_suite )

add_executable( request_response_lifecycle_feature_test_suite ${SOURCE_DIR}/request_response_lifecycle.cpp )
target_link_libraries( request_response_lifecycle_feature_test_suite ${STATIC_LIBRARY_NAME} )
add_test( request_response_lifecycle_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_response_lifecycle_feature_test_suite )

add_executable( transfer_encoding_feature_test_suite ${SOURCE_DIR}/transfer_encoding.cpp )
target_link_libraries( transfer_encoding_feature_test_suite ${STATIC_LIBRARY_NAME} )
add_test( transfer_encoding_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/transfer_encoding_feature_test_suite )
