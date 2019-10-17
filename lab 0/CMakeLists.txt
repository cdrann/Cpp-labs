cmake_minimum_required(VERSION 3.14)
project(word_count)

set(CMAKE_CXX_STANDARD 17)

add_executable(word_count main.cpp Writer.cpp Writer.h Reader.cpp Reader.h)