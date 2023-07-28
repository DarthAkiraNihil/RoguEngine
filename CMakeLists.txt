cmake_minimum_required(VERSION 3.23)
project(RoguEngine)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

file(GLOB SOURCES include/conio21/*.*)
        include_directories(${CMAKE_SOURCE_DIR})

set(SFML_STATIC_LIBRARIES TRUE)

include_directories(${CMAKE_SOURCE_DIR}/include/SFML/include)
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/include/fmt/include)

## In most cases better set in the CMake cache
set(SFML_DIR "${CMAKE_SOURCE_DIR}/include/SFML/lib/cmake/SFML")

add_subdirectory(include/fmt EXCLUDE_FROM_ALL)

find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)

add_library(RoguEngine library.cpp)

add_executable(RELocTest testing/loctest.cpp ${SOURCES})

add_executable(RESFMLTest testing/sfmltest.cpp ${SOURCES})

add_executable(RESCTest testing/sctest.cpp ${SOURCES})

target_link_libraries(RESFMLTest sfml-graphics sfml-audio)
target_link_libraries(RESCTest sfml-graphics sfml-audio fmt::fmt-header-only)









