cmake_minimum_required(VERSION 3.8)
project(ceng477)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES parser.cpp ppm.cpp tinyxml2.cpp raytracer.cpp)
add_executable(ceng477 ${SOURCE_FILES})