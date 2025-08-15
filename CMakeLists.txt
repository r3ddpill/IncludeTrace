cmake_minimum_required(VERSION 3.10)
project(IncludeTrace)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(IncludeTrace
    src/main.cpp
    src/include_graph.cpp
    src/scanner.cpp
)
