#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <error.h>

typedef struct Allocator {
    size_t capacity;
    bool heap_alloc;
    void *ctx;
} Allocator;

Error allocator_init(size_t max_cap, void *buffer, Allocator *out);
/* Apenas o alocator que acessa a heap necessita ser liberado explicitamente.
Em via de regra devemos tentar evitar ao maximo alocações dinamicas pós-inicialização.
Se possivel toda memoria deve ser pré-alocada na inicialização. */
Error allocator_heap_init(size_t max_cap, Allocator *out);
Error allocator_heap_destroy(Allocator *allocator);

/* O allocator é uma estrutura muito simples. Ele apenas faz uma coisa. Ele aloca um bloco contiguo de memoria
de um tamanho especificado em sua capacity.
Ele é extremamente burro. E isso é uma feature proposital.
Seu unico proposito é de alocar um bloco.
O que será feito com esse bloco cabe as estrategias que vão o utilizar.

Desta maneira se torna necessário apena ter noção de que uma alocação em memoria ocorreu, pela existencia de um allocator.
O unico momento em que free(ptr) é evocado no codigo é nos momentos em que o allocator será liberado. 
Isso reduz muito a carga cognitiva necessária para fazer manejo de memoria manual e diminui as chances de bugs
como use after free ou memory leaks. Afinal desta maneira uma memory leak potencialmente seria direcionada
a um allocator inteiro que foi esquecido de ser removido e não a uma alocação minima perdida pelo código.

Em termos mais gerais:
    The allocator owns the memory.
    Strategies decide how that memory is used. 
    Data structures consume the buffers provided by those strategies 
*/