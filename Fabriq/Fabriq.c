//
// Created by Covald on 09.05.2024.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "Fabriq.h"
#include "utils/darray.h"
#include "Entities/new.h"
#include "Entities/Point.h"
#include "Entities/circle.h"
#include "Entities/rectangle.h"
#include "Entities/line.h"

#define BUFF_SIZE 256

static void *parse_line(char *str) {
    char objName[BUFF_SIZE];
    char tmp[BUFF_SIZE] = "\0";

    int x1, y1, x2, y2;

    int n = sscanf(str, "%s %d %d %d %d %s", objName, &x1, &y1, &x2, &y2, tmp);

    objName[BUFF_SIZE - 1] = '\0';

    if (n <= 0) return NULL;

    if (n >= 6 || *tmp != '\0') {
        printf("Incorrect param count in str(cnt params - %d): %s\n", n-1, str);
        return NULL;
    } else if (!strcmp(objName, "point") && n == 3) {
        return new(Point, x1, y1);
    } else if (!strcmp(objName, "circle") && n == 4) {
        return new(Circle, x1, y1, x2);
    } else if (!strcmp(objName, "rect") && n == 5) {
        return new(Rectangle, x1, y1, x2, y2);
    } else if (!strcmp(objName, "line") && n == 5) {
        return new(Line, x1, y1, x2, y2);
    } else {
        printf("Incorrect param count in str(cnt params - %d): %s\n", n-1, str);
        return NULL;
    }
}

static inline void destroy_prt(void *ptr) {
    delete(*(void **) ptr);
}

void *parse_file(FILE *fp) {
    void *shapes = darray_create(sizeof(void *));

    if (shapes == NULL) {
        darray_destroy(shapes, destroy_prt);
        printf("Can't allocate memory for array of shapes.");
        return NULL;
    }

    char str[BUFF_SIZE];
    while (fgets(str, BUFF_SIZE, fp)) {
        void *shape = parse_line(str);
        if (!shape) { continue; }
        void **tmp = (void **) darray_add(shapes);
        if (tmp == NULL) {
            delete(shape);
            printf("Can't get memory for next item.\n");
            break;
        }
        *tmp = shape;
    }

    return shapes;
}
