cmake_minimum_required(VERSION 3.30)
project(Comp)

set(CMAKE_CXX_STANDARD 20)

add_executable(main.cpp
        LexAnalyzer.cpp
        LexAnalyzer.h
        SyntaxAnalyzer.h
        SyntaxAnalyzer.cpp
        interpretor.cpp)
