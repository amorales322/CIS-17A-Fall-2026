cmake_minimum_required(VERSION 4.2)
project(CIS_17A_Fall_2026)

set(CMAKE_CXX_STANDARD 26)
add_compile_definitions(rsize_t=size_t)

add_executable(CIS_17A_Fall_2026 Project/Project1/main.cpp
        Project/Project1/moveCalculations.cpp
        Project/Project1/Array.cpp
        Project/Project1/Board.cpp
        Project/Project1/Player.cpp
        Project/Project1/Piece.cpp
        Project/Project1/Coord.cpp)
