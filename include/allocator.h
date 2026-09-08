#include <stdbool.h>
#include <stddef.h>
#include "error.h"

typedef struct Allocator {
    size_t capacity;
    bool heap_alloc;
    void *ctx;

    void *(*alloc)(void* ctx, size_t size);
    Error (*free)(void *ctx, void *ptr);
    void *(*realloc)(void *ctx, void *ptr, size_t size);
} Allocator;

Error allocator_init(size_t max_cap, void *buffer, Allocator *out);
Error allocator_heap_init(size_t max_cap, Allocator *out);
Error allocator_destroy(Allocator *allocator);
