cmake_minimum_required( VERSION 3.0 )
project( cerescurve )

set( CMAKE_CXX_FLAGS "-std=c++14 -O3" )
set( CMAKE_BUILD_TYPE Release )

find_package( OpenCV REQUIRED )
find_package( Ceres REQUIRED )

include_directories( /usr/include/eigen3)
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${Ceres_INCLUDE_DIRS} )

add_executable( ok cerescurvefitting.cpp )

target_link_libraries( ok ${OpenCV_LIBS} ${CERES_LIBRARIES} )