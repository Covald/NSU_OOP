cmake_minimum_required(VERSION 3.22)
project(2D_scene C)

set(CMAKE_C_STANDARD 11)

add_executable(2D_scene main.c Entities/new.c Entities/new.h
        Entities/Shape.c
        Entities/Shape.h
        Entities/Point.c
        Entities/Point.h
        Fabriq.c
        Fabriq.h
        utils/queue.c
        Entities/circle.c
        Entities/circle.h
        Entities/rectangle.c
        Entities/rectangle.h
        Entities/line.c
        Entities/line.h)
