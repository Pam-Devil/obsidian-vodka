#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stack.h>

Stack *create_stack(size_t capacity, size_t item_size)
{
    if (capacity == 0)
        return NULL;
    if (item_size == 0)
        return NULL;
    if (capacity > SIZE_MAX / item_size)
        return NULL;

    void *data = malloc(capacity * item_size);
    if (!c_assert(data != NULL))
        return NULL;

    Stack *buff = malloc(sizeof(Stack));
    if (!c_assert(buff != NULL))
    {
        free(data);
        return NULL;
    }

    *buff = (Stack){
        .capacity = capacity,
        .size = 0,
        .item_size = item_size,
        .data = data};

    return buff;
}

Error add_to_stack(Stack *buff, void *item, size_t item_size)
{
    if (buff == NULL)
        return ERROR;
    if (item == NULL)
        return ERROR;
    if (item_size == 0)
        return ERROR;
    if (item_size != buff->item_size)
        return ERROR;
    if (buff->size == buff->capacity)
        return ERROR; // Isso eu nao vejo problema, pode acontecer da stack ta cheia, so nao faz nada.
    if (!c_assert(buff->size < buff->capacity))
        return ERROR; // Ja aqui temos um absurdo. Então vale o assert

    void *top = (char *)buff->data + buff->size * buff->item_size;
    (void)memcpy(top, item, buff->item_size);
    buff->size++;

    return SUCCESS;
}

Error destroy_stack(Stack **buff)
{
    if (buff == NULL || *buff == NULL)
        return ERROR;

    free((*buff)->data);
    free(*buff);

    *buff = NULL;

    return SUCCESS;
}

Error peek_stack(Stack *buff, void *out)
{
    if (buff == NULL)
        return ERROR;
    if (buff->data == NULL)
        return ERROR;
    if (buff->size == 0)
        return ERROR;
    if (out == NULL)
        return ERROR;
    if (!c_assert(buff->size <= buff->capacity))
        return ERROR;

    void *top = (char *)buff->data + (buff->size - 1) * buff->item_size;
    (void)memcpy(out, top, buff->item_size);
    return SUCCESS;
}

Error pop_stack(Stack *buff, void *out)
{
    if (buff == NULL)
        return ERROR;
    if (buff->data == NULL)
        return ERROR;
    if (buff->size == 0)
        return ERROR;
    if (out == NULL)
        return ERROR;

    if (!c_assert(buff->size <= buff->capacity))
        return ERROR;

    void *top = (char *)buff->data + (buff->size - 1) * buff->item_size;
    (void)memcpy(out, top, buff->item_size);

    buff->size--;

    return SUCCESS;
}

void printarr(void *arr, size_t size, size_t capacity, size_t item_size, void (*print_item)(void *))
{
    printf("Buffer: [ ");
    for (size_t i = 0; i < size; i++)
    {
        void *element = (char *)arr + i * item_size;

        print_item(element);
        printf(", ");
    }
    printf("\\\\] \n");
}

void print_int(void *item){
    printf("%d", *(int *)item);
}
void print_char(void *item){
    printf("%c", *(char *)item);
}