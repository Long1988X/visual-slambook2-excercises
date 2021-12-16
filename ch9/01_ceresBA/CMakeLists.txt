cmake_minimum_required( VERSION 3.0 )

project( BUNDLE_ADJUSTMET )

set( CMAKE_CXX_FLAGS "-std=c++14 -O2" )
set( CMAKE_BUILD_TYPE Release )
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package( Eigen3 REQUIRED )
find_package( Sophus REQUIRED )
find_package( Ceres REQUIRED )

include_directories( ${PROJECT_SOURCE_DIR} ${EIGEN3_INCLUDE_DIR} ${CERES_INCLUDE_DIRS})

add_library(bal_common common.cpp)

add_executable( ok bundle_adjustment_ceres.cpp )

target_link_libraries( ok Sophus::Sophus )
target_link_libraries( ok ${CERES_LIBRARIES} bal_common)