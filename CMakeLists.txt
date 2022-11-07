cmake_minimum_required(VERSION 3.12)
project (umcdi)

include_directories ( 
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/include/display
	${CMAKE_SOURCE_DIR}/include/transport
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory (transport)
add_subdirectory (display)

