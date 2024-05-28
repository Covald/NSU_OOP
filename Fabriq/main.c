#include <stdio.h>
#include "Fabriq.h"
#include "Entities/new.h"
#include "utils/darray.h"

static void destroy_prt(void *ptr) {
    delete(*(void **) ptr);
}

int main(int argc, char *argv[]) {
    const char *file_name = NULL;
    if (argc > 1)
        file_name = argv[1];
    if (file_name == NULL) {
        printf("Can't get filename for input file.\n");
        printf("Usage: ./2D_scene input_filename.\n");
        return -1;
    }

    FILE *input_file = (FILE *) fopen(file_name, "r");

    if (input_file == NULL) {
        printf("Can't open the input file - %s.", file_name);
        return -1;
    }

    void *shapes = parse_file(input_file);

    fclose(input_file);

    if (shapes == NULL) {
        printf("Can't allocate memory for array of shapes.");
        return -1;
    }

    for (size_t i = darray_first(shapes); i != darray_stop(shapes); i = darray_next(shapes, i)) {
        draw(*(void **) darray_current(shapes, i));
    }
    darray_destroy(shapes, destroy_prt);
    return 0;
}
