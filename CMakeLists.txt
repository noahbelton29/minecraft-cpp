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

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES
        "src/*.cpp"
        "external/glad/src/*.c"
)

add_executable(minecraft ${SOURCES})

target_include_directories(minecraft PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/glad/include
)

target_link_libraries(minecraft PRIVATE
        glfw
        ${OPENGL_LIBRARIES}
)