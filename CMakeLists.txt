cmake_minimum_required (VERSION 3.1 FATAL_ERROR)
project(MCTS_Navigation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(src)
add_subdirectory(samples)
