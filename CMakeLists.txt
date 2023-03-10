cmake_minimum_required(VERSION 3.22)
project(DL)

set(CMAKE_CXX_STANDARD 23)

add_executable(DL main.cpp src/matrix.cpp src/vector2.cpp)
