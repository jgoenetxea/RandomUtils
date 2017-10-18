cmake_minimum_required( VERSION 2.8 )
project( rotMatFrom3dVector )

find_package( OpenCV REQUIRED )

set( SRCS
	main.cpp
)

include_directories( ${OpenCV_INCLUDE_DIRS} )
link_directories( ${CMAKE_BINARY_DIR}/bin )
add_executable( ${PROJECT_NAME} ${SRCS} )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

