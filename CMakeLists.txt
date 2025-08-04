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
        src/MemoryRegion.cpp
        src/MemoryRegion.h
        src/ui/ProcListWindow.cpp
        src/ui/ProcListWindow.h
        src/ui/ProcDetailsWindow.cpp
        src/ui/ProcDetailsWindow.h
        src/analysis/MemoryScanner.cpp
        src/analysis/MemoryScanner.h
)

target_include_directories(proc_view PRIVATE ${SOL2_INCLUDE_DIRS} ${LUA_INCLUDE_DIRS})
target_link_libraries(proc_view PRIVATE sol2::sol2 ${LUA_LIBRARIES} Qt6::Widgets)
