//
// Created by Covald on 09.05.2024.
//
#include "stdio.h"
#include "Point.h"
#include "new.h"
#include "stdarg.h"

static void *Point_ctor(void *_self, va_list *app) {
    struct Point *self = _self;
    if (((const class *) Shape)->ctor != NULL) {
        self = ((const class *) Shape)->ctor(_self, app);
    }

    if (self == NULL) { return NULL; }

    self->x = va_arg(*app, int);
    self->y = va_arg(*app, int);

    return self;
}

static void Point_draw(const void *_self) {
    const struct Point *self = _self;

    printf("point at (%d, %d)\n", self->x, self->y);
}

static const class _Point = {
        sizeof(struct Point),
        Point_ctor,
        0,
        Point_draw
};

const void *Point = &_Point;