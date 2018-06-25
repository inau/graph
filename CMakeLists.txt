cmake_minimum_required(VERSION 3.8)
project(Graph)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES library.cpp library.h)
add_library(Graph ${SOURCE_FILES})

add_executable(TestExe main.cpp)
target_link_libraries(TestExe Graph)