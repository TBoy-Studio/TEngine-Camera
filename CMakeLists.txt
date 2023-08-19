cmake_minimum_required(VERSION 3.10)

project(tengine-camera VERSION 1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Used by clang language server for code completion
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# Build as static lib
set(BUILD_SHARED_LIBS False)

# Build with all warnings enabled and optimize maximally
add_compile_options(-Wall -Wextra -Wpedantic -O3)

# Include directories for header files
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/submodules/cglm/include)


add_library( ${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/camera.c )

target_link_libraries( ${PROJECT_NAME} PRIVATE m cglm_headers )

add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/cglm EXCLUDE_FROM_ALL)