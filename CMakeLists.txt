cmake_minimum_required(VERSION 3.12)
project (umcdi)

set(PICO_SDK_FETCH_FROM_GIT On)
include(pico_sdk_import.cmake)

include(bcm2835_import.cmake)

include_directories ( 
	/usr/include
	/usr/local/include
	${CMAKE_SOURCE_DIR}/include
)

pico_sdk_init()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(umcdi
	display/display.cpp
	display/ST7735.cpp
	transport/transport.cpp
	transport/BCM2835_hw_spi.cpp
	transport/BCM2835_sw_spi.cpp
	transport/RP2040_hw_spi.cpp
)

target_link_libraries(umcdi pico_stdlib)
