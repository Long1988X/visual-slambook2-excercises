cmake_minimum_required( VERSION 3.0 )

set( CMAKE_CXX_FLAGS "-std=c++14 -O3" )
set( CMAKE_BUILD_TYPE Release )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( ok triangulation.cpp )

target_link_libraries( ok ${OpenCV_LIBS} )