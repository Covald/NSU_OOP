//
// Created by Covald on 09.05.2024.
//
#include "stdio.h"
#include "rectangle.h"
#include "new.h"

static void *Rectangle_ctor(void *_self, va_list *app) {
    struct Rectangle *self = _self;
    if (((const class *) Shape)->ctor != NULL) {
        self = ((const class *) Shape)->ctor(_self, app);
    }
    if (self == NULL) { return NULL; }

    self->x_1 = va_arg(*app, int);
    self->y_1 = va_arg(*app, int);
    self->x_2 = va_arg(*app, int);
    self->y_2 = va_arg(*app, int);

    return self;
}

static void Rectangle_draw(const void *_self) {
    const struct Rectangle *self = _self;

    printf("rect at (%d, %d), (%d, %d)\n", self->x_1, self->y_1, self->x_2, self->y_2);
}

static const class _Rectangle = {
        sizeof(struct Rectangle),
        Rectangle_ctor,
        0,
        Rectangle_draw
};

const void *Rectangle = &_Rectangle;