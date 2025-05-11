cmake_minimum_required(VERSION 3.31)
project(proc_view)

set(CMAKE_CXX_STANDARD 20)

add_executable(proc_view src/main.cpp
        src/Process.cpp
        src/Process.h
        src/System.cpp
        src/System.h
)
