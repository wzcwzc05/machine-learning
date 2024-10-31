cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(libmatrix STATIC utils/matrix.cpp)
target_include_directories(libmatrix PUBLIC include utils)

add_executable(MyProgram src/main.cpp)
target_link_libraries(MyProgram PRIVATE libmatrix)
