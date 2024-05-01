cmake_minimum_required(VERSION 3.22)
project(darray C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(darray main.c
        darray.c darray.h
        temp.c
        slist.h)
