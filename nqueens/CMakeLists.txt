cmake_minimum_required(VERSION 3.21)
project(nqueens)

set(CMAKE_CXX_STANDARD 14)

add_executable(nqueens main.cpp TextTable.h BruteForce.h)
