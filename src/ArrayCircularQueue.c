#define LINKED_LIST_IMPLEMENTATION
#include "..\include\linked_list_DEQueue.h"

void print_int(int value) {
    printf("%d", value);
}
void print_char(char value) {
    printf("%c", value);
}
void print_float(float value) {
    printf("%f", value);
}

int main(){
    List_int* Lista = DEQueue_int_create();
    DEQueue_int_enqueue_head(Lista , 1);
    DEQueue_int_enqueue_head(Lista , 2);
    DEQueue_int_enqueue_tail(Lista , 3);
    DEQueue_int_enqueue_tail(Lista , 4);
    printf("Primero %d\n", DEQueue_int_first(Lista));
    printf("Ultimo %d\n", DEQueue_int_last(Lista));
    DEQueue_int_print(Lista, print_int);
    DEQueue_int_dequeue_tail(Lista);
    printf("Primero %d\n", DEQueue_int_first(Lista));
    printf("Ultimo %d\n", DEQueue_int_last(Lista));
    DEQueue_int_print(Lista, print_int);
    DEQueue_int_dequeue_head(Lista);
    DEQueue_int_dequeue_head(Lista);
    DEQueue_int_dequeue_tail(Lista);
    printf("Vacia %i\n", DEQueue_int_is_empty(Lista));
    return 0;
}