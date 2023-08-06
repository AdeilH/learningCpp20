cmake_minimum_required(VERSION 3.0.0)
project(DSMPP VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(DSMPP main.cpp "c++20/source_location_example.hpp" "c++20/ranges_example.hpp")
