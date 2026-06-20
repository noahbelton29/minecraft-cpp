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
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.3
        GIT_SHALLOW true
)
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master
        GIT_SHALLOW true
)

FetchContent_MakeAvailable(glfw glm stb)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES
        "src/*.cpp"
        "external/glad/src/*.c"
)

add_executable(minecraft ${SOURCES})

target_include_directories(minecraft PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/glad/include
        ${stb_SOURCE_DIR}
)

target_link_libraries(minecraft PRIVATE
        glfw
        glm::glm
        ${OPENGL_LIBRARIES}
)
