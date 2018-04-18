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

add_executable( response_constructor_unit_test_suite ${SOURCE_DIR}/response/constructor.cpp )
target_link_libraries( response_constructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( response_constructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_constructor_unit_test_suite )

add_executable( response_destructor_unit_test_suite ${SOURCE_DIR}/response/destructor.cpp )
target_link_libraries( response_destructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( response_destructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_destructor_unit_test_suite )

add_executable( response_getters_unit_test_suite ${SOURCE_DIR}/response/getters.cpp )
target_link_libraries( response_getters_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( response_getters_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_getters_unit_test_suite )

add_executable( response_has_header_unit_test_suite ${SOURCE_DIR}/response/has_header.cpp )
target_link_libraries( response_has_header_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( response_has_header_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_has_header_unit_test_suite )

add_executable( response_setters_unit_test_suite ${SOURCE_DIR}/response/setters.cpp )
target_link_libraries( response_setters_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( response_setters_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_setters_unit_test_suite )

add_executable( settings_constructor_unit_test_suite ${SOURCE_DIR}/settings/constructor.cpp )
target_link_libraries( settings_constructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( settings_constructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/settings_constructor_unit_test_suite )

add_executable( settings_destructor_unit_test_suite ${SOURCE_DIR}/settings/destructor.cpp )
target_link_libraries( settings_destructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( settings_destructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/settings_destructor_unit_test_suite )

add_executable( settings_getters_unit_test_suite ${SOURCE_DIR}/settings/getters.cpp )
target_link_libraries( settings_getters_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( settings_getters_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/settings_getters_unit_test_suite )

add_executable( settings_setters_unit_test_suite ${SOURCE_DIR}/settings/setters.cpp )
target_link_libraries( settings_setters_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( settings_setters_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/settings_setters_unit_test_suite )

add_executable( session_close_unit_test_suite ${SOURCE_DIR}/session/close.cpp )
target_link_libraries( session_close_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_close_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_close_unit_test_suite )

add_executable( session_constructor_unit_test_suite ${SOURCE_DIR}/session/constructor.cpp )
target_link_libraries( session_constructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_constructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_constructor_unit_test_suite )

add_executable( session_destructor_unit_test_suite ${SOURCE_DIR}/session/destructor.cpp )
target_link_libraries( session_destructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_destructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_destructor_unit_test_suite )

add_executable( session_fetch_unit_test_suite ${SOURCE_DIR}/session/fetch.cpp )
target_link_libraries( session_fetch_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_fetch_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_fetch_unit_test_suite )

add_executable( session_getters_unit_test_suite ${SOURCE_DIR}/session/getters.cpp )
target_link_libraries( session_getters_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_getters_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_getters_unit_test_suite )

add_executable( session_observe_unit_test_suite ${SOURCE_DIR}/session/observe.cpp )
target_link_libraries( session_observe_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_observe_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_observe_unit_test_suite )

add_executable( session_open_unit_test_suite ${SOURCE_DIR}/session/open.cpp )
target_link_libraries( session_open_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_open_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_open_unit_test_suite )

add_executable( session_send_unit_test_suite ${SOURCE_DIR}/session/send.cpp )
target_link_libraries( session_send_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_send_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_send_unit_test_suite )

add_executable( session_setters_unit_test_suite ${SOURCE_DIR}/session/setters.cpp )
target_link_libraries( session_setters_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_setters_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_setters_unit_test_suite )

add_executable( session_yield_unit_test_suite ${SOURCE_DIR}/session/yield.cpp )
target_link_libraries( session_yield_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_yield_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_yield_unit_test_suite )
