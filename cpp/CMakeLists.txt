cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0)
set(CMAKE_COMPILER_IS_GNUCXX true)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -std=c++17")

include_directories(include)
add_library(libmatrix utils/matrix.cpp)
add_executable(MyProgram src/main.cpp)
target_link_libraries(MyProgram libmatrix)

