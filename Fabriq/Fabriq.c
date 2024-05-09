//
// Created by Covald on 09.05.2024.
//

#include <stdio.h>
#include <string.h>
#include "Fabriq.h"
#include "utils/queue.h"
#include "Entities/new.h"
#include "Entities/Point.h"
#include "Entities/circle.h"
#include "Entities/rectangle.h"
#include "Entities/line.h"

#define BUFF_SIZE 256

static void *parse_line(char *str) {
    char objName[BUFF_SIZE];
    int x, y, z, w;
    int num = sscanf(str, "%s %d %d %d %d", objName, &x, &y, &z, &w);

    objName[BUFF_SIZE - 1] = '\0';

    if (num == -1) return NULL;
    else if (!strcmp(objName, "point")) return new(Point, x, y);
    else if (!strcmp(objName, "circle")) return new(Circle, x, y, z);
    else if (!strcmp(objName, "rect")) return new(Rectangle, x, y, z, w);
    else if (!strcmp(objName, "line")) return new(Line, x, y, z, w);
    else {
        printf("Incorrect param count in str: %s\n", str);
        return NULL;
    }
}

void *parse_file(char *filename) {

    FILE *fp = fopen(filename, "r");
    if (!fp) { return NULL; }

    void *queue = queue_init();

    char str[BUFF_SIZE];
    while (fgets(str, BUFF_SIZE, fp)) {
        void *shape = parse_line(str);
        if (!shape) { continue; }
        if (!enqueue(queue, shape)) { break; }
    }

    fclose(fp);
    return queue;
}
