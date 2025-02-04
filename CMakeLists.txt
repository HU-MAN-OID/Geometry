cmake_minimum_required(VERSION 3.25)

project(Kantarion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Kantarion STATIC
    Geometry/Geometry.h Geometry/Geometry.cpp
    Geometry/Point.h
    Geometry/Segment.h
)

target_link_libraries(Kantarion rt)
target_compile_definitions(Kantarion PRIVATE KANTARION_LIBRARY)
add_subdirectory(GeometryTests/Point)
add_subdirectory(GeometryTests/Segment)
