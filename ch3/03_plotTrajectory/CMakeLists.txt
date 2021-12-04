cmake_minimum_required( VERSION 3.10 )

set( CMAKE_CXX_FLAGS "-std=c++11" )

# 添加Pangolin依赖
find_package( Pangolin REQUIRED )

include_directories( /usr/include/eigen3 )
include_directories( ${Pangolin_INCLUDE_DIRS} )

add_executable( ok plotTrajectory.cpp )

target_link_libraries( ok ${Pangolin_LIBRARIES} )