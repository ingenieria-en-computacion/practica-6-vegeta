#define LINKED_LIST_IMPLEMENTATION
#include "..\include\linked_list_Circular_Queue.h"

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
    List_int* Lista = CircularQueue_int_create();
    CircularQueue_int_enqueue(Lista , 1);
    CircularQueue_int_enqueue(Lista , 2);
    CircularQueue_int_enqueue(Lista , 3);
    CircularQueue_int_enqueue(Lista , 4);
    printf("Primero %d\n", CircularQueue_int_first(Lista));
    printf("Ultimo %d\n", CircularQueue_int_first(Lista));
    CircularQueue_int_print(Lista, print_int);
    CircularQueue_int_dequeue(Lista);
    printf("Primero %d\n", CircularQueue_int_first(Lista));
    printf("Ultimo %d\n", CircularQueue_int_first(Lista));
    CircularQueue_int_print(Lista, print_int);
    CircularQueue_int_dequeue(Lista);
    CircularQueue_int_dequeue(Lista);
    CircularQueue_int_dequeue(Lista);
    printf("Vacia %i\n", CircularQueue_int_is_empty(Lista));
    return 0;
}