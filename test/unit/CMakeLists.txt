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
add_executable( request_constructor_unit_test_suite ${SOURCE_DIR}/request/constructor.cpp )
target_link_libraries( request_constructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( request_constructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_constructor_unit_test_suite )

add_executable( request_destructor_unit_test_suite ${SOURCE_DIR}/request/destructor.cpp )
target_link_libraries( request_destructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( request_destructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_destructor_unit_test_suite )

add_executable( request_getters_unit_test_suite ${SOURCE_DIR}/request/getters.cpp )
target_link_libraries( request_getters_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( request_getters_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_getters_unit_test_suite )

add_executable( request_setters_unit_test_suite ${SOURCE_DIR}/request/setters.cpp )
target_link_libraries( request_setters_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( request_setters_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_setters_unit_test_suite )
