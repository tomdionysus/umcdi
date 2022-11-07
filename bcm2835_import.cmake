# This can be dropped into an external project to help locate this SDK
# It should be include()ed prior to project()

include(FetchContent)

if (NOT BCM2835_LIB_PATH)
    set(FETCHCONTENT_BASE_DIR_SAVE ${FETCHCONTENT_BASE_DIR})

    FetchContent_Declare(
        bcm2835_lib
        GIT_REPOSITORY https://github.com/matthiasbock/bcm2835
        GIT_TAG master
        GIT_SUBMODULES_RECURSE FALSE
    )

    if (NOT bcm2835_lib)
        message("Downloading BCM2835 Library")
        FetchContent_Populate(bcm2835_lib)
        set(BCM2835_LIB_PATH ${bcm2835_lib_SOURCE_DIR})
    endif ()
endif ()

get_filename_component(BCM2835_LIB_PATH "${BCM2835_LIB_PATH}" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
if (NOT EXISTS ${BCM2835_LIB_PATH})
    message(FATAL_ERROR "Directory '${BCM2835_LIB_PATH}' not found")
endif ()