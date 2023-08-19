cmake_minimum_required(VERSION 3.10)

project(camera VERSION 0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS True) # So clang can do code completion

# Global Options
set(BUILD_SHARED_LIBS False)

add_compile_options(-Wall -Wextra -Wpedantic -O3)

add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/cglm)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/submodules/cglm/include)

add_library(
    tengine-camera
    ${PROJECT_SOURCE_DIR}/src/camera.c
)

target_link_libraries(tengine-camera PRIVATE m cglm)