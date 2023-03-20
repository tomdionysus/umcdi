include(FetchContent)

FetchContent_Declare(
    bcm2835
    GIT_REPOSITORY https://github.com/matthiasbock/bcm2835
    GIT_TAG master
)

FetchContent_MakeAvailable(bcm2835)

include_directories(${bcm2835_lib_SOURCE_DIR}/src)
