# CMakeLists.txt

project(BinarySearchTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(BinarySearchTree STATIC ${CMAKE_CURRENT_SOURCE_DIR}/source/BinarySearchTree.cpp)

add_executable(Examples ${CMAKE_CURRENT_SOURCE_DIR}/examples/main.cpp)
