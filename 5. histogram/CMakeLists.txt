cmake_minimum_required(VERSION 3.22)
project(Histogram)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(src)

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)
