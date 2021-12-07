cmake_minimum_required( VERSION 3.0 )

set( CMAKE_CXX_FLAGS "-std=c++11" )
set( CMAKE_BUILD_TYPE Release )

find_package( Pangolin REQUIRED )
find_package( OpenCV REQUIRED )

include_directories( ${Pangolin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} )

add_executable( ok stereovision.cpp )

target_link_libraries( ok ${Pangolin_LIBRARIES} ${OpenCV_LIBS} )