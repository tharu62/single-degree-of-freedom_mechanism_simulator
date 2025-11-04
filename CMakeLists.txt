cmake_minimum_required(VERSION 3.28)
project(single-degree-of-freedom_mechanism_simulator LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

include(FetchContent)
FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG 5.5
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(raylib)

add_executable(main src/main.c)
target_compile_features(main PRIVATE c_std_17)

target_link_libraries(main PRIVATE raylib)
