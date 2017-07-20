cmake_minimum_required(VERSION 3.7)
project(DV)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        evaluation-visitor.h
        evaluation-visitor.cpp
        visitor.h
        ast.h
        print-visitor.cpp
        print-visitor.h)
add_executable(DV ${SOURCE_FILES})