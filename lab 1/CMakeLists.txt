cmake_minimum_required(VERSION 3.14)
project(trilean)

set(CMAKE_CXX_STANDARD 14)

add_executable(trilean main.cpp Tests.cpp catch.hpp Traitset.h Traitset.cpp Trait_operations.h Trait_operations.cpp)