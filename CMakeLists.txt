cmake_minimum_required(VERSION 3.10)

project(raytracer VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(include)
add_subdirectory(src)
