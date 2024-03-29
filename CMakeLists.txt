cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)
include(bcm2835_import.cmake)

project(umcdi CXX C ASM)

pico_sdk_init()

include_directories ( 
	${CMAKE_SOURCE_DIR}/src
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(
	umcdi

	src/display.cpp
	src/ST7735.cpp
	
	src/transport.cpp
	src/BCM2835_hw_spi.cpp
	src/RP2040_hw_spi.cpp
)
target_link_libraries(umcdi pico_stdlib hardware_spi bcm2835)

# Examples

project(rp2040_st7735 CXX C ASM)
add_executable(
	rp2040_st7735
	examples/RP2040_ST7735/main.cpp
)
pico_add_extra_outputs(rp2040_st7735)
target_link_libraries(rp2040_st7735 umcdi)

project(bcm2835_st7735 CXX C)
add_executable(
	bcm2835_st7735
	examples/BCM2835_ST7735/main.cpp
)
target_link_libraries(bcm2835_st7735 umcdi)
