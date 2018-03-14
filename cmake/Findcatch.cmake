find_path( catch_INCLUDE catch.hpp HINTS "${PROJECT_SOURCE_DIR}/dependency/protocol/dependency/core/dependency/catch/single_include" )

if ( catch_INCLUDE )
    set( CATCH_FOUND TRUE )
    message( STATUS "Located Catch include at: ${catch_INCLUDE}" )
else ( )
    message( FATAL_ERROR "Failed to locate Catch dependency." )
endif ( )
