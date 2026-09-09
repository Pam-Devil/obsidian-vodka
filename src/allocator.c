#include <allocator.h>
#include <stdlib.h>

Error allocator_init(size_t max_cap, void *buffer, Allocator *out){
    if(out == NULL) return ERROR;
    if(buffer == NULL) return ERROR;

    *out = (Allocator){
        .capacity = max_cap,
        .heap_alloc = false,
        .ctx = buffer
    };
    return SUCCESS;
}

Error allocator_heap_init(size_t max_cap, Allocator *out){
    if(out == NULL) return ERROR;

    void *buffer = malloc(max_cap);

    if (!c_assert(buffer != NULL)) return ERROR;

    *out = (Allocator){
        .capacity = max_cap,
        .heap_alloc = true,
        .ctx = buffer
    };

    return SUCCESS;
}

Error allocator_heap_destroy(Allocator *allocator){
    if(allocator == NULL) return ERROR;
    if(allocator->ctx == NULL) return ERROR;

    if(allocator->heap_alloc != true) return ERROR;

    free(allocator->ctx);

    allocator->ctx = NULL;

    *allocator = (Allocator){0};

    return SUCCESS;
}