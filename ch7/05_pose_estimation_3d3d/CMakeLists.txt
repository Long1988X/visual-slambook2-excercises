cmake_minimum_required( VERSION 3.0 )

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_BUILD_TYPE Release )
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules/")

find_package( Sophus REQUIRED )
find_package( G2O REQUIRED )
find_package( OpenCV REQUIRED )

include_directories( "/usr/include/eigen3" ${Sophus_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${G2O_INCLUDE_DIRS} )

add_executable( ok pose_estimation_3d3d.cpp )

target_link_libraries( ok Sophus::Sophus )
target_link_libraries( ok ${OpenCV_LIBS} ${Sophus_LIBRARIES} ${G2O_CORE_LIBRARY} ${G2O_STUFF_LIBRARY} )