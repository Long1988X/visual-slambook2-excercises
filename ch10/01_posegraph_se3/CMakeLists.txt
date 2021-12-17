cmake_minimum_required( VERSION 3.0 )

project( pose_graph )

set( CMAKE_CXX_FLAGS "-std=c++11 -O2" )
set( CMAKE_BUILD_TYPE Release )

list( APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules" )

find_package( G2O REQUIRED )

set( G2O_LIBS g2o_core g2o_stuff g2o_types_slam3d )

include_directories( ${G2O_INCLUDE_DIRS} "/usr/include/eigen3" )

add_executable( ok pose_graph_g2o_SE3.cpp )

target_link_libraries( ok ${G2O_LIBS} ${CHOLMOD_LIBRARIES})