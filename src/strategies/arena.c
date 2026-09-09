#include <arena.h>
#include <string.h>
#include <stdint.h>

Error create_arena(Allocator* buff, size_t capacity, Arena* out){
    if(buff == NULL) return ERROR;
    if(out == NULL) return ERROR;
    if(buff->ctx == NULL) return ERROR;
    if(capacity > buff->capacity) return ERROR;

    *out = (Arena){
        .capacity = capacity,
        .size = 0,
        .arena = buff->ctx
    };

    return SUCCESS;
}

Error add_to_arena(Arena* arena, size_t item_size, void* item, void** out){
    if(arena == NULL) return ERROR;
    if(out == NULL) return ERROR;
    if(*out == NULL) return ERROR;
    if(item == NULL) return ERROR;
    if(arena->arena == NULL) return ERROR;
    if(item_size + arena->size > arena->capacity) return ERROR;

    //posicao atual do slot vazio da arena
    void *ptr = (uint8_t *)arena->arena + arena->size; 

    memcpy(ptr, item, item_size);

    *out = ptr;

    arena->size += item_size;

    return SUCCESS;
}
Error clear_arena(Arena* arena){
    if(arena == NULL) return ERROR;
    arena->size = 0;
    
    return SUCCESS;
}