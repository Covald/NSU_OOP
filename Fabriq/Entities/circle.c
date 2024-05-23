//
// Created by Covald on 09.05.2024.
//

#include "circle.h"
#include <stdio.h>
#include "new.h"

static void *Circle_ctor(void *_self, va_list *app) {
    struct Circle *self = (struct Circle *) _self;
    if (((const class *) Point)->ctor != NULL)
        self = ((const class *) Point)->ctor(_self, app);

    if (self == NULL) { return NULL; }

    self->rad = va_arg(*app, int);

    return self;
}

#define x(p) (((const struct Point *)(p)) -> x)
#define y(p) (((const struct Point *)(p)) -> y)

static void Circle_draw(const void *_self) {
    const struct Circle *self = _self;

    printf("circle at (%d, %d) rad = %d\n", x(self), y(self), self->rad);
}

static const class _Circle = {
        sizeof(struct Circle),
        Circle_ctor,
        0,
        Circle_draw
};

const void *Circle = &_Circle;