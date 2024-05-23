//
// Created by Covald on 09.05.2024.
//
#include "stdio.h"
#include "line.h"
#include "new.h"

static void *Line_ctor(void *_self, va_list *app) {
    struct Line *self = _self;
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

static void Line_draw(const void *_self) {
    const struct Line *self = _self;

    printf("line - (%d, %d) -> (%d, %d)\n", self->x_1, self->y_1, self->x_2, self->y_2);
}

static const class _Line = {
        sizeof(struct Line),
        Line_ctor,
        0,
        Line_draw
};

const void *Line = &_Line;