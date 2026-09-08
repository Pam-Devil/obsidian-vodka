#include <allocator.h>

typedef struct Arena {
    size_t capacity;
    size_t size;
    void* arena;
} Arena;

Error create_arena(Allocator* buff, size_t capacity, Arena* out);
Error add_to_arena(Arena* arena, size_t item_size, void* item, void* out);
Error clear_arena(Arena* arena);

/* A ideia da arena é ser um espaço de memoria onde varios itens são alocados de uma vez, 
mesmo itens de tamanhos diferentes, contanto que todos possuam o mesmo lifetime. 
Não existe uma operação de "remover um item da arena", uma vez que um item da arena precisa morrer,
deve se garantir que todos os outros itens da arena também devem morrer.
Caso contrario temos uma violação do proposito da arena que é todos compartilhem o mesmo lifetime.

Por exemplo ao abrir um arquivo, podemos alocar diversas coisas. como a string do arquivo,
allocar um objeto referente ao parsing desse arquivo e etc, porém no momento que o arquivo nao é mais
necessario, todo ele + sua serialização devem morrer. Caso seja necessário manter a serialização mas não a string do arquivo,
o ideal é criar uma copia da serialização em outra alocação. 

*/