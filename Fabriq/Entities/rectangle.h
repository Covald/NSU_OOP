//
// Created by Covald on 09.05.2024.
//

#ifndef INC_2D_SCENE_RECTANGLE_H
#define INC_2D_SCENE_RECTANGLE_H

#include "Shape.h"

struct Rectangle {
    const struct Shape _;
    int x_1, y_1, x_2, y_2;
};

extern const void *Rectangle;
#endif //INC_2D_SCENE_RECTANGLE_H
