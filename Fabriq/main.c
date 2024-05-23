#include <stdio.h>
#include "Fabriq.h"
#include "Entities/new.h"
#include "utils/darray.h"

void destroy_prt(void *ptr) {
    delete(*(void **) ptr);
}

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
    for (size_t i = darray_first(shapes); i != darray_stop(shapes); i = darray_next(shapes, i)) {
        draw(*(void **) darray_current(shapes, i));
    }
    darray_destroy(shapes, destroy_prt);
    return 0;
}
