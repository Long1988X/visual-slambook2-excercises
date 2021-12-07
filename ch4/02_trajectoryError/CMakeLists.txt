cmake_minimum_required( VERSION 3.10 )

set( CMAKE_CXX_FLAGS "-std=c++11" )

find_package( Sophus REQUIRED ) 
find_package( Pangolin REQUIRED )

include_directories( /usr/include/eigen3 )
include_directories( ${Sophus_INCLUDE_DIRS} ${Pangolin_INCLUDE_DIRS})

add_executable( ok trajectoryError.cpp )

target_link_libraries( ok Sophus::Sophus )
target_link_libraries( ok ${Sophus_LIBRARIES} ${Pangolin_LIBRARIES} )