cmake_minimum_required(VERSION 3.5)
project(Multiplication)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package (Boost COMPONENTS unit_test_framework REQUIRED)

set(SOURCE_FILES tests.cpp Multiplication.cpp Multiplication.h)
add_executable(Multiplication ${SOURCE_FILES})