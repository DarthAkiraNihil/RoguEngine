cmake_minimum_required(VERSION 3.23)
project(RoguEngine)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

include_directories(${CMAKE_SOURCE_DIR})

add_library(RoguEngine library.cpp)






