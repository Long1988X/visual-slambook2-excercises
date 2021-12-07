cmake_minimum_required( VERSION 3.0 )

find_package( Sophus REQUIRED )
find_package( Pangolin REQUIRED )
find_package( OpenCV REQUIRED )


include_directories( ${Sophus_INCLUDE_DIRS} ${Pangolin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

find_package(Pangolin REQUIRED)

add_executable( joinMap joinMap.cpp )

target_link_libraries( joinMap Sophus::Sophus )
target_link_libraries( joinMap ${OpenCV_LIBS} ${Pangolin_LIBRARIES} ${Sophus_LIBRARIES} )