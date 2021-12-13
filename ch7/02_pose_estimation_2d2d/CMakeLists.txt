cmake_minimum_required( VERSION 3.0 )

set( CMAKE_CXX_FLAGS "-std=c++14 -O3" ) 
set( CMAKE_BUILD_TYPE Release )

find_package( OpenCV )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( ok pose_estimation_2d2d.cpp )

target_link_libraries( ok ${OpenCV_LIBS} )