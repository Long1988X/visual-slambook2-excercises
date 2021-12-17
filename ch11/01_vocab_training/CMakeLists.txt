cmake_minimum_required( VERSION 3.0 )

set( CMAKE_CXX_FLAGS "-std=c++11 -O2" )
set( CMAKE_BUILD_TYPE Release )

find_package( OpenCV REQUIRED )
find_package( DBoW3 REQUIRED )

include_directories( ${DBoW3_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} )

add_executable( ok vocab_trainning.cpp )

target_link_libraries( ok ${DBoW3_LIBS} ${OpenCV_LIBS} )