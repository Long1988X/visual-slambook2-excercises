cmake_minimum_required( VERSION 3.0 )

set( CMAKE_CXX_FLAGS "-std=c++11 -O2" )
set( CMAKE_BUILD_TYPE Release )

find_package( Boost REQUIRED )
find_package( Sophus REQUIRED )
find_package( OpenCV REQUIRED )

include_directories( "/usr/include/eigen3" ${Boost_INCLUDE_DIRS} ${Sophus_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} )

add_executable( ok dense_mapping.cpp )

target_link_libraries( ok Sophus::Sophus )
target_link_libraries( ok ${Boost_LIBRARIES} ${Sophus_LIBRARIES} ${OpenCV_LIBRARIES} )