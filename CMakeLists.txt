cmake_minimum_required(VERSION 3.10)

project(bulk CXX)

option(BUILD_TESTS "Build unittests" OFF)

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(lib)

add_executable(bulk main.cpp)

target_link_libraries(bulk lib)
