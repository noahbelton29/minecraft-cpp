cmake_minimum_required(VERSION 4.2)
project(minecraft)

include(FetchContent)
include_directories(include/)

set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
        GIT_SHALLOW true
)
FetchContent_MakeAvailable(glfw)

add_executable(minecraft src/main.cpp src/core/window.cpp src/minecraft.cpp)
target_link_libraries(minecraft PRIVATE glfw)