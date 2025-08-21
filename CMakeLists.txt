cmake_minimum_required(VERSION 3.10)
project(Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(calculator
    src/Calculator.cpp
    src/Lexicography.cpp
    src/Parser.cpp
    src/main.cpp
)