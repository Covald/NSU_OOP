//
// Created by Covald on 09.05.2024.
//

#include "Shape.h"
#include "new.h"

static const class _Shape = {
        sizeof(struct Shape),
        0,
        0,
        0
};
const void *Shape = &_Shape;