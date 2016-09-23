cmake_minimum_required(VERSION 2.8)
project(BinarySearchTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES source/BinarySearchTree.cpp include/BinarySearchTree.h)
add_executable(BinarySearchTree ${SOURCE_FILES} examples/main.cpp )
