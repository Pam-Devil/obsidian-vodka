#pragma once

#include <allocator.h>
#include <stdint.h>

typedef struct Pool {
    size_t capacity;
    size_t used;
    size_t block_size;

    void* pool;

    uint64_t* bitmap;
} Pool;

Error create_pool(Allocator* buff, size_t capacity, size_t block_size, uint64_t* bitmap, Pool* pool);

Error add_to_pool(Pool* pool, size_t item_size, void* item, void* out, size_t* out_index);

Error get_item_index(Pool* pool, void* item, size_t* out_index);
Error get_item(Pool* pool, size_t index, void** out);

Error remove_from_pool(Pool* pool, void* item);
Error index_remove_from_pool(Pool* pool, size_t index);

Error clear_pool(Pool* pool);

/* A ideia da pool é ser uma divisão do bloco de memoria em subblocos de tamanhos iguais.
estes subblocos são acessados por indices pool_index
Os blocos tem por sua vez a ideia de serem reutilizaveis.
Os slots de uma pool são reutilizáveis: quando um item deixa de ser necessário, 
seu espaço pode ser reutilizado por outro item do mesmo tamanho.. 
*/

/*
Um exemplo bem simples seria um efeito de onda sonora ASCII

#
###
#####
##
###
######
####
##
###
#####
###
##
#
#####

aqui podemos imaginar que cada coluna da visualização é uma stack de maximo 5 itens
porém como temos uma lista destas stacks, podemos modelar esse problema como uma pool de n stacks de m itens.
*/