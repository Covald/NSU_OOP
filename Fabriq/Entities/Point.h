//
// Created by Covald on 09.05.2024.
//

#ifndef INC_2D_SCENE_POINT_H
#define INC_2D_SCENE_POINT_H
// Стандартная преамбула для заголовочного файла, гарантирующая его однократное
// включение

#include "Shape.h"

// Структура объекта класса Circle
struct Point {
    const struct Shape _;
    int x, y;
};

extern const void *Point;
#endif