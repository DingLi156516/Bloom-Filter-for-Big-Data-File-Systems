cmake_minimum_required(VERSION 3.8)
project(BF_project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Mapping.cpp Mapping.h Function.h Function.cpp DirNode.h DirNode.cpp FSTree.h FSTree.cpp Benchmark.cpp Benchmark.h)
add_executable(BF_project ${SOURCE_FILES})