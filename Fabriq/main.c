#include <stdio.h>
#include "Fabriq.h"
#include "Entities/new.h"
#include "utils/queue.h"

int main(int argc, char *argv[]) {
    const char *file_name = NULL;
    if (argc > 1)
        file_name = argv[1];
    if (file_name == NULL) {
        printf("no input file\n");
        return -1;
    }

    void *shapes = parse_file(file_name);
    if (shapes == NULL) {
        printf("no figures\n");
        return -1;
    }
    for (size_t i = 0; i < queue_count(shapes); ++i)
        draw(queue_get(shapes, i));

    queue_destroy(shapes, delete);
    return 0;
}