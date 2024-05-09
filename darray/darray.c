#include <stdlib.h>
#include <string.h>
#include "darray.h"

typedef struct {
    size_t capacity;
    size_t count;
    size_t itemSize;
    char *items;
} DynamicArray;

static void *_get_item_ptr(DynamicArray *arr, size_t idx) {
    return arr->items + idx * arr->itemSize;
}

static bool _realloc(DynamicArray *arr) {
    if (arr->count >= arr->capacity) {
        size_t temp_cap = arr->capacity * 2;
        char *temp = realloc(arr->items, temp_cap * arr->itemSize);
        if (temp) return false;
        arr->items = temp;
        arr->capacity = temp_cap;
    }
    return true;
}

void *darray_create(size_t itemSize) {
    if (itemSize == 0) return NULL;

    DynamicArray *darray = malloc(sizeof(DynamicArray));
    if (darray == NULL) return NULL;

    darray->capacity = 10;
    darray->count = 0;
    darray->itemSize = itemSize;
    darray->items = malloc(darray->capacity * itemSize);
    if (darray->items == NULL) {
        free(darray);
        return NULL;
    }

    return darray;
}

void darray_destroy(void *darray, void(*destroy)(void *)) {
    if (darray == NULL) return;

    DynamicArray *arr = (DynamicArray *) darray;
    darray_clear(arr, destroy);

    free(arr->items);
    free(arr);
}

void *darray_init(void *darray, size_t itemSize, void(*destroy)(void *)) {
    if (darray == NULL) return NULL;
    if (itemSize == 0) return NULL;
    DynamicArray *arr = (DynamicArray *) darray;

    darray_clear(darray, destroy);
    free(arr->items);

    arr->capacity = 10;
    arr->count = 0;
    arr->itemSize = itemSize;

    arr->items = malloc(itemSize * arr->capacity);
    if (arr->items == NULL) {
        free(arr);
        return NULL;
    }

    return arr;
}

void darray_clear(void *darray, void(*destroy)(void *)) {
    if (darray == NULL) return;

    DynamicArray *arr = (DynamicArray *) darray;
    if (destroy != NULL) {
        for (size_t i = 0; i < arr->count; ++i) {
            destroy(_get_item_ptr(arr, i));
        }
    }
    arr->count = 0;
}

size_t darray_count(const void *darray) {
    if (darray == NULL) return INVALID;

    return ((DynamicArray *) darray)->count;
}

void *darray_item(void *darray, size_t i) {
    if (darray == NULL || i >= darray_count(darray)) return NULL;

    return _get_item_ptr(darray, i);
}

void *darray_add(void *darray) {
    if (darray == NULL) return NULL;

    DynamicArray *arr = (DynamicArray *) darray;
    bool is_success = _realloc(arr);
    if (!is_success) return NULL;

    return _get_item_ptr(arr, arr->count++);
}

void *darray_insert(void *darray, size_t i) {
    if (darray == NULL || i > darray_count(darray)) return NULL;

    DynamicArray *arr = (DynamicArray *) darray;
    bool is_success = _realloc(arr);
    if (!is_success) return NULL;

    memmove((char *) arr->items + (i + 1) * arr->itemSize,
            (char *) arr->items + i * arr->itemSize,
            (arr->count - i) * arr->itemSize);

    arr->count++;
    return _get_item_ptr(arr, i);
}

void darray_remove(void *darray, size_t i, void(*destroy)(void *)) {
    if (darray == NULL || i >= darray_count(darray)) return;

    DynamicArray *arr = (DynamicArray *) darray;
    if (destroy != NULL) {
        destroy(_get_item_ptr(arr, i));
    }
    memmove((char *) arr->items + i * arr->itemSize,
            (char *) arr->items + (i + 1) * arr->itemSize,
            (arr->count - i - 1) * arr->itemSize);

    arr->count--;
}

size_t darray_first(const void *darray) {
    if (darray == NULL || darray_stop(darray) == 0) return darray_stop(darray);
    return 0;
}

size_t darray_last(const void *darray) {
    if (darray == NULL || darray_stop(darray) == 0) return darray_stop(darray);
    return darray_count(darray) - 1;
}

size_t darray_next(const void *darray, size_t item_id) {
    if (darray == NULL || item_id >= darray_stop(darray)) return darray_stop(darray);

    return ++item_id;
}

size_t darray_prev(const void *darray, size_t item_id) {
    if (darray == NULL || item_id >= darray_stop(darray) || item_id == 0) return darray_stop(darray);

    return --item_id;
}

size_t darray_stop(const void *darray) {
    return darray_count(darray);
}

void *darray_current(const void *darray, size_t item_id) {
    if (darray == NULL || item_id >= darray_stop(darray)) return NULL;

    return _get_item_ptr((void *) darray, item_id);
}

void darray_erase(void *darray, size_t item_id, void(*destroy)(void *)) {
    if (darray == NULL || item_id >= darray_stop(darray)) return;

    darray_remove(darray, item_id, destroy);
}
