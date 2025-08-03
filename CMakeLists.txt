cmake_minimum_required(VERSION 3.20)
project(proc_view)

set(CMAKE_CXX_STANDARD 23)

find_package(sol2 REQUIRED)
find_package(Lua REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

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

target_include_directories(proc_view PRIVATE ${SOL2_INCLUDE_DIRS} ${LUA_INCLUDE_DIRS})
target_link_libraries(proc_view PRIVATE sol2::sol2 ${LUA_LIBRARIES} Qt6::Widgets)
