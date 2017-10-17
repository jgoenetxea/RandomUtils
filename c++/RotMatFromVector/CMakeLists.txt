cmake_minimum_required( VERSION 2.8 )
project( sily_opencv_test )

find_package( OpenCV REQUIRED )

set( SRCS
	main.cpp
)

include_directories( ${OpenCV_INCLUDE_DIRS} )
link_directories( ${CMAKE_BINARY_DIR}/bin )
add_executable( sily_opencv_test ${SRCS} )
target_link_libraries( sily_opencv_test ${OpenCV_LIBS} )

add_definitions(-DASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
