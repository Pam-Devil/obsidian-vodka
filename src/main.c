#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arena.h>
#define MAX_BUFF 4096

/* Um exemplo de uso de stacks com essa arquitetura 
Primeiro criamos o allocator para obter um bloco de memoria
Depois associamos uma estrategia de uso a esse bloco
Por fim, usamos a estrategia para fornecer a uma estrutura de dados o espaço onde ela vai viver
*/

int main(){
    uint8_t buffer[MAX_BUFF]; //Alocamos exatamente 4096 bytes
    Allocator alloc;
    Error e = allocator_init(sizeof(buffer), buffer, &alloc);

    if(e != SUCCESS) printf("Erro ao allocar memoria no allocator");
    else printf("Sucesso ao allocar memoria");

    printf("\n Buffer: \n%p", (void *)buffer);
    printf("\n Allocator: \n%p", alloc.ctx);
    printf("\n Allocados: %zu", alloc.capacity);

    printf("\n ----------------------------- \n");

    Arena ar;
    e = create_arena(&alloc, alloc.capacity, &ar);
    
    if(e != SUCCESS) printf("Erro ao criar a arena \n");
    else printf("Sucesso ao criar a arena \n");
   
    uint8_t item[256];
    void *item_ptr;
    e = add_to_arena(&ar, sizeof(item), item, &item_ptr);

    if(e != SUCCESS) printf("Erro ao adicionar item a arena \n");
    else printf("Sucesso ao adicionar item a arena \n");

    printf("\n Item: \n%p", (void *)item);
    printf("\n Arena location: \n%p", (void *)item_ptr);
    printf("\n Proximo slot: \n%p", (uint8_t *)ar.arena + ar.size);
    printf("\n Allocados: %zu", ar.size);

    uint8_t item_2[256];
    void *item_ptr_2;
    e = add_to_arena(&ar, sizeof(item_2), item_2, &item_ptr_2);

    if(e != SUCCESS) printf("Erro ao adicionar item a arena \n");
    else printf("Sucesso ao adicionar item a arena \n");

    printf("\n Item: \n%p", (void *)item_2);
    printf("\n Arena location: \n%p", (void *)item_ptr_2);
    printf("\n Proximo slot: \n%p", (uint8_t *)ar.arena + ar.size);
    printf("\n Allocados: %zu", ar.size);

    printf("\n ----------------------------- \n");
    (void)clear_arena(&ar);
    printf("\n Proximo slot: \n%p", (uint8_t *)ar.arena + ar.size);
    printf("\n Allocados: %zu", ar.size);

    return 0;
}