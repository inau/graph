cmake_minimum_required(VERSION 3.8)
project(Graph)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES library.cpp library.h source/IGraph.h source/CEdge.h source/CVertex.h source/CGraph.h source/IAlgo.h source/ITopologies.h source/IValueGenerators.h source/IGraphUtil.h)
add_library(Graph ${SOURCE_FILES})

add_executable(TestExe main.cpp)
target_link_libraries(TestExe Graph)