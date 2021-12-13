cmake_minimum_required( VERSION 3.0 )

# set( CMAKE_CXX_FLAGS "-std=c++14 -O3" )
set(CMAKE_CXX_STANDARD 14)
set( CMAKE_BUILD_TYPE Release )

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules/")

find_package( Ceres REQUIRED )
find_package( OpenCV REQUIRED )
find_package( G2O REQUIRED )

include_directories( /usr/include/eigen3 )
include_directories( ${CERES_INCLUDE_DIRS})
include_directories( ${OpenCV_INCLUDE_DIRS})
include_directories( ${G20_INCLUDE_DIRS} )

add_executable( ok g2oCurveFitting.cpp )

target_link_libraries( ok ${OpenCV_LIBS} ${CERES_LIBRARIES} ${G2O_CORE_LIBRARY} ${G2O_STUFF_LIBRARY} )