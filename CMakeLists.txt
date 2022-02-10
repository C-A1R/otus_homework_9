cmake_minimum_required (VERSION 3.2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
 
project (async)
 
add_subdirectory(src_lib)
add_subdirectory(src_test)

enable_testing()