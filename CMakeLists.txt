cmake_minimum_required(VERSION 3.23)
project(Ynex)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-O3)

add_executable(Ynex main.cpp lexer.cpp compiler.h parser.cpp emitter.cpp)