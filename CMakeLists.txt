cmake_minimum_required(VERSION 3.31)
project(proc_view)

set(CMAKE_CXX_STANDARD 23)

add_executable(proc_view src/main.cpp
        src/Process.cpp
        src/Process.h
        src/System.cpp
        src/System.h
        src/ProcessAnalyzer.cpp
        src/ProcessAnalyzer.h
        src/MemoryRegion.cpp
        src/MemoryRegion.h
)
