cmake_minimum_required( VERSION 3.0 )

project( BUNDLE_ADJUSTMENT )

set( CMAKE_CXX_FLAGS "-std=c++14 -O3" )
set( CMAKE_BUILD_TYPE Release )

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package( Eigen3 REQUIRED )
find_package( Sophus REQUIRED )
find_package( G2O REQUIRED )
find_package( CSparse REQUIRED )

set( G2O_LIBS g2o_csparse_extension g2o_stuff g2o_core cxsparse )

include_directories( ${PROJECT_SOURCE_DIR} ${EIGEN3_INCLUDE_DIR} ${CSPARSE_INCLUDE_DIR} )

add_library( bal_common common.cpp )
add_executable( ok bundle_adjustment_g2o.cpp )

target_link_libraries( ok Sophus::Sophus )
target_link_libraries( ok ${G2O_LIBS} bal_common )