include(FetchContent)

FetchContent_Declare(
    bcm2835_lib
    GIT_REPOSITORY https://github.com/matthiasbock/bcm2835
    GIT_TAG master
)

FetchContent_MakeAvailable(bcm2835_lib)

include_directories(${bcm2835_lib_SOURCE_DIR}/src)
