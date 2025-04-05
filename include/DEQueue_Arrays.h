#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// ----------------------------
// Macro para declarar estructuras y prototipos
// ----------------------------

#define DECLARE_CIRCULAR_QUEUE(TYPE) \
    typedef struct { \
        TYPE* posicion;/*son los datos pero declarados de forma conveneinte para poder referirse, por ejemplo, a posicion[1] (lo que está en la posición 1)*/\
        int head; \
        int tail; \
        size_t length; \
    } Circular_Queue_##TYPE; \
    \
    /*Operaciones de las Colas circulares (CircularQueue) implementadas como lista ligada*/\
    Circular_Queue_##TYPE* CircularQueue_##TYPE##_create(void); \
    void CircularQueue_##TYPE##_destroy( Circular_Queue_##TYPE* CircularQueue);\
    void CircularQueue_##TYPE##_print(const Circular_Queue_##TYPE* CircularQueue, void (*print_fn)(TYPE));\
    void CircularQueue_##TYPE##_enqueue( Circular_Queue_##TYPE* CircularQueue, TYPE data);\
    void CircularQueue_##TYPE##_dequeue( Circular_Queue_##TYPE* CircularQueue);\
    TYPE CircularQueue_##TYPE##_first(const Circular_Queue_##TYPE* CircularQueue);\
    TYPE CircularQueue_##TYPE##_last(const Circular_Queue_##TYPE* CircularQueue);\
    bool CircularQueue_##TYPE##_is_empty(const Circular_Queue_##TYPE* CircularQueue);\
    void CircularQueue_##TYPE##_empty(const Circular_Queue_##TYPE* CircularQueue);\
// ----------------------------
// Macro para implementación
// ----------------------------
#define IMPLEMENT_CIRCULAR_QUEUE(TYPE) \
    Circular_Queue_##TYPE* CircularQueue_##TYPE##_create(void){\
        /*Se crea la cola circular con malloc, se inician head y tail en -1 porque aún no hay datos, y se inicia la longitud de la cola en 0*/\
        Circular_Queue_##TYPE* new_Queue = (Circular_Queue_##TYPE*)malloc(sizeof(Circular_Queue_##TYPE));\
        if(!new_Queue) return NULL;\
        new_Queue->head = -1;\
        new_Queue->tail = -1;\
        new_Queue->length = 0;\
        new_Queue->posicion = (TYPE*)malloc(sizeof(TYPE)*10);\
        return new_Queue;\
    }\
    void CircularQueue_##TYPE##_destroy( Circular_Queue_##TYPE* CircularQueue){\
        /*si se pasa una cola no nula, se libera  la cola, borrándola*/ \
        if(!CircularQueue) return;\
        free(CircularQueue);\
    }\
    void CircularQueue_##TYPE##_print(const CircularQueue_##TYPE* CircularQueue, void (*print_fn)(TYPE)){\
        /*si la cola y la función para imprimir existen, se recorre el arreglo de la cola con un for*/ \
        if (!CircularQueue || !print_fn) return; \
        \
        printf("[ "); \
        for(int i = 0; i<CircularQueue->length;i++){\
            print_fn(CircularQueue->posicion[i]);\
            if (i<CircularQueue->length-1)printf(", ");\
        }\
        printf("]\n"); \
    }\
    void CircularQueue_##TYPE##_enqueue( Circular_Queue_##TYPE* CircularQueue, TYPE data){\
        /*si la cola está vacía, se inician head y tail en 0, se pone el dato deseado en la posición 0 del arreglo, y length es 1*/\
        if(CircularQueue_##TYPE##_is_empty(CircularQueue)){\
            CircularQueue->head =0;\
            CircularQueue->tail = 0;\
            CircularQueue->posicion[0]= data;\
            CircularQueue->length=1;\
            return;\
        }\
        /*si la longitud de la cola es igual al tamaño del arreglo entre el tamaño del dato (los datos que se están guardando actualmente en la cola ) se agranda el arreglo*/ \
        if(CircularQueue->length == sizeof(CircularQueue->posicion)/sizeof(TYPE)) CircularQueue->posicion = realloc(CircularQueue->posición, CircularQueue->length+1);\
        /*se aumentan tail y length para reflejar que se añadirá un elemento, se pone el dato deseado en el espacio correcto*/\
        CircularQueue->tail ++;\
        CircularQueue->length ++;\
        CircularQueue->posicion[CircularQueue->tail] = data;\
    }\
    void CircularQueue_##TYPE##_dequeue( Circular_Queue_##TYPE* CircularQueue){\
        /*Si la cola está vacía, no se puede desencolar , no se hace nada más. si sólo había un elemento, se restablecen los valores default, y si no es ninguna, se mueven los elementos para desencolar*/\
        if(CircularQueue_##TYPE##_is_empty(CircularQueue)){\
            printf("la cola está vacía");\
            return;\
        }\
        if(CircularQueue->length==1){\
            CircularQueue->head =-1;\
            CircularQueue->tail = -1;\
            CircularQueue->length=0;\
            return;\
        }\
        /*se recorren los elemenots y se cambian length y tail, quitando el elemento en 0 y preservando la estructura de la cola correctamente*/\
        for(int i = 0; i<CircularQueue->length-1;i++){\
            CircularQueue->posicion[i]=CircularQueue->posicion[i+1];\
        }\
        CircularQueue->length--;\
        CircularQueue->tail--;\
    }\
    TYPE CircularQueue_##TYPE##_first(const Circular_Queue_##TYPE* CircularQueue){\
        /*si la cola está vacía se imprime un error y se manda el '0' como error con el tipo apropiado. si no está vacía, se retorna el primer dato (posición 0)*/\
        if(!CircularQueue_##TYPE##_is_empty(CircularQueue)){\
            printf("cola vacía");\
            return (TYPE)0;\
        }\
        return CircularQueue->posicion[0];\
    }\
    TYPE CircularQueue_##TYPE##_last(const Circular_Queue_##TYPE* CircularQueue){\
        /*si la cola está vacía se imprime un error y se manda el '0' como error con el tipo apropiado. si no está vacía, se retorna el último dato (posición tail)*/\
        if(!CircularQueue_##TYPE##_is_empty(CircularQueue)){\
            printf("cola vacía");\
            return (TYPE)0;\
        }\
        return CircularQueue->posicion[CircularQueue->tail];\
    }\
    bool CircularQueue_##TYPE##_is_empty(const Circular_Queue_##TYPE* CircularQueue){\
        /*si la longitud es 0, retorna verdad, si no, retorna falso*/\
        return CircularQueue->length==0;\
    }\
    void CircularQueue_##TYPE##_empty(const Circular_Queue_##TYPE* CircularQueue){\
        /*se restablecen los valores default a como si estuviera vacía.*/\
        CircularQueue->head =-1;\
            CircularQueue->tail = -1;\
            CircularQueue->length=0;\
    }\
DECLARE_CIRCULAR_QUEUE(int)
DECLARE_CIRCULAR_QUEUE(char)
DECLARE_CIRCULAR_QUEUE(float)

// ----------------------------
// Implementación para tipos concretos
// ----------------------------
#ifdef CIRCULAR_QUEUE_IMPLEMENTATION
IMPLEMENT_CIRCULAR_QUEUE(int)
IMPLEMENT_CIRCULAR_QUEUE(char)
IMPLEMENT_CIRCULAR_QUEUE(float)
#endif