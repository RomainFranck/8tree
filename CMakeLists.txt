cmake_minimum_required  ( VERSION 3.0 )
project ( 8tree )

set ( CMAKE_CXX_STANDARD 14 )

set ( SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/main.cpp 
        ${PROJECT_SOURCE_DIR}/src/Voxel.cpp )

set ( CMAKE_CXX_FLAGS "-g -Wall -pedantic")

include_directories (   ${PROJECT_SOURCE_DIR}/include )

set ( EXECUTABLE_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/bin  )

add_executable  ( 8tree ${SOURCE_FILES} )
