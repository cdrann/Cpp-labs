cmake_minimum_required(VERSION 3.14)
project(CSVParser)

set(CMAKE_CXX_STANDARD 17)

add_executable(CSVParser main.cpp csv_parser.h parser_error.h tuple_fill.h tuple_print.h)