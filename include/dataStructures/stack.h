#pragma once

#include <error.h>
#include <stddef.h>

/* Apesar de estarmos usando allocators e strategies, as data-structures não precisam se importar
com esses detalhes de implementação. Tudo que uma data-structure precisa é acesso a um espaço de memoria
onde ela vai viver.
Ou seja, não há acoplação entre uma data-structure e nossa arquitetura.
Isso permite as estruturas continuarem existindo e interagindo entre si mesmo em sistemas que não utilizem
a mesma arquitetura.
Tudo que nossa arquitetura faz é simplificar o processo de alocação e manutenção de lifetimes. Ela não tem
opnião alguma sobre como os dados serão usados, acessados ou interagidos. 
Quem define isso e a propria estrutura de dados. */

typedef struct
{
    size_t capacity;
    size_t size;
    size_t item_size;

    void *data;
} Stack;

Stack *create_stack(size_t capacity, size_t item_size);

Error add_to_stack(Stack *buff, void *item, size_t item_size);

Error destroy_stack(Stack **buff);

Error peek_stack(Stack *buff, void *out);

Error pop_stack(Stack *buff, void *out);
