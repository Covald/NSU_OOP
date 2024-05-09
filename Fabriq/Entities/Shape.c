//
// Created by Covald on 09.05.2024.
//

#include "Shape.h"
#include "new.h"

static void *Shape_ctor(void *_self, va_list *app) {
    struct Shape *self = NULL;
    if (_self) {
        self = (struct Shape *) _self;
    }
    return self;
}

static const class _Shape = {
        sizeof(struct Shape),
        Shape_ctor,
        0,
        0
};
const void *Shape = &_Shape;