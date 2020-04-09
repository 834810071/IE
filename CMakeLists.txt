cmake_minimum_required(VERSION 3.13)
project(IE)

set(CMAKE_CXX_STANDARD 14)

set(lib
        test.cpp
        time_heap.cpp
        time_heap.h)

add_library(Lib ${lib})

add_executable(IE main.cpp)
add_executable(test test.cpp)
add_executable(epoll epoll源码注释.c)

target_link_libraries(IE Lib pthread)
target_link_libraries(test Lib pthread)