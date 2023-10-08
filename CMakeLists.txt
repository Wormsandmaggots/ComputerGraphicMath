cmake_minimum_required(VERSION 3.25)
project(aMatematykaGrafiki)

set(CMAKE_CXX_STANDARD 23)
include_directories(inc)

add_executable(aMatematykaGrafiki main.cpp inc/Vector.h src/Vector.cpp inc/Matrix.h src/Matrix.cpp)
