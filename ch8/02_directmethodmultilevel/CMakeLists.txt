cmake_minimum_required( VERSION 3.0 )

set( CMAKE_CXX_FLAGS "-std=c++14 -O2" )
set( CMAKE_BUILD_TYPE Release )

find_package( OpenCV REQUIRED )
find_package( Sophus REQUIRED )
find_package( Pangolin REQUIRED )

include_directories( /usr/include/eigen3/ )
include_directories( ${OpenCV_INCLUDE_DIRS} ${Sophus_INCLUDE_DIRS} ${Pangolin_INCLUDE_DIRS} )

add_executable( ok direct_method.cpp )

target_link_libraries( ok Sophus::Sophus )
target_link_libraries( ok ${OpenCV_LIBS} ${Sophus_LIBRRIES} ${Pangolin_LIBRARIES} )