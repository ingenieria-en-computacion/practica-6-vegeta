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
    } D_E_Queue_##TYPE; \
    \
    /*Operaciones de las Colas circulares (DEQueue) implementadas como lista ligada*/\
    D_E_Queue_##TYPE* DEQueue_##TYPE##_create(void); \
    void DEQueue_##TYPE##_destroy( D_E_Queue_##TYPE* DEQueue);\
    void DEQueue_##TYPE##_print(const D_E_Queue_##TYPE* DEQueue, void (*print_fn)(TYPE));\
    void DEQueue_##TYPE##_enqueue_head( D_E_Queue_##TYPE* DEQueue, TYPE data);\
    void DEQueue_##TYPE##_dequeue_head( D_E_Queue_##TYPE* DEQueue);\
    void DEQueue_##TYPE##_enqueue_tail( D_E_Queue_##TYPE* DEQueue, TYPE data);\
    void DEQueue_##TYPE##_dequeue_tail( D_E_Queue_##TYPE* DEQueue);\
    TYPE DEQueue_##TYPE##_first(const D_E_Queue_##TYPE* DEQueue);\
    TYPE DEQueue_##TYPE##_last(const D_E_Queue_##TYPE* DEQueue);\
    bool DEQueue_##TYPE##_is_empty(const D_E_Queue_##TYPE* DEQueue);\
    void DEQueue_##TYPE##_empty(const D_E_Queue_##TYPE* DEQueue);\
// ----------------------------
// Macro para implementación
// ----------------------------
#define IMPLEMENT_CIRCULAR_QUEUE(TYPE) \
    D_E_Queue_##TYPE* DEQueue_##TYPE##_create(void){\
        /*Se crea la cola circular con malloc, se inician head y tail en -1 porque aún no hay datos, y se inicia la longitud de la cola en 0*/\
        D_E_Queue_##TYPE* new_Queue = (D_E_Queue_##TYPE*)malloc(sizeof(D_E_Queue_##TYPE));\
        if(!new_Queue) return NULL;\
        new_Queue->head = -1;\
        new_Queue->tail = -1;\
        new_Queue->length = 0;\
        new_Queue->posicion = (TYPE*)malloc(sizeof(TYPE)*10);\
        return new_Queue;\
    }\
    void DEQueue_##TYPE##_destroy( D_E_Queue_##TYPE* DEQueue){\
        /*si se pasa una cola no nula, se libera  la cola, borrándola*/ \
        if(!DEQueue) return;\
        free(DEQueue->posicion);\
        free(DEQueue);\
    }\
    void DEQueue_##TYPE##_print(const DEQueue_##TYPE* DEQueue, void (*print_fn)(TYPE)){\
        /*si la cola y la función para imprimir existen, se recorre el arreglo de la cola con un for*/ \
        if (!DEQueue || !print_fn) return; \
        \
        printf("[ "); \
        for(int i = 0; i<DEQueue->length;i++){\
            print_fn(DEQueue->posicion[i]);\
            if (i<DEQueue->length-1)printf(", ");\
        }\
        printf("]\n"); \
    }\
    void DEQueue_##TYPE##_enqueue_head( D_E_Queue_##TYPE* DEQueue, TYPE data){\
        /*si la cola está vacía, se inician head y tail en 0, se pone el dato deseado en la posición 0 del arreglo, y length es 1*/\
        if(DEQueue_##TYPE##_is_empty(DEQueue)){\
            DEQueue->head =0;\
            DEQueue->tail = 0;\
            DEQueue->posicion[0]= data;\
            DEQueue->length=1;\
            return;\
        }\
        /*si la longitud de la cola es igual al tamaño del arreglo entre el tamaño del dato (los datos que se están guardando actualmente en la cola ) se agranda el arreglo*/ \
        if(DEQueue->length == sizeof(DEQueue->posicion)/sizeof(TYPE)) DEQueue->posicion = realloc(DEQueue->posición, DEQueue->length+1);\
        /*se recorren los elementos para hacer espacio antes de head para poner elelemento deseado*/\
        for(int i = DEQueue->length ; i>0;i--){\
            DEQueue->posicion[i]=DEQueue->posicion[i-1];\
        }\
        /*se aumentan tail y length para reflejar que se añadirá un elemento, se pone el dato deseado en el espacio correcto*/\
        DEQueue->tail ++;\
        DEQueue->length ++;\
        DEQueue->posicion[0] = data;\
    }\
    void DEQueue_##TYPE##_enqueue_tail( D_E_Queue_##TYPE* DEQueue, TYPE data){\
        /*si la cola está vacía, se inician head y tail en 0, se pone el dato deseado en la posición 0 del arreglo, y length es 1*/\
        if(DEQueue_##TYPE##_is_empty(DEQueue)){\
            DEQueue->head =0;\
            DEQueue->tail = 0;\
            DEQueue->posicion[0]= data;\
            DEQueue->length=1;\
            return;\
        }\
        /*si la longitud de la cola es igual al tamaño del arreglo entre el tamaño del dato (los datos que se están guardando actualmente en la cola ) se agranda el arreglo*/ \
        if(DEQueue->length == sizeof(DEQueue->posicion)/sizeof(TYPE)) DEQueue->posicion = realloc(DEQueue->posición, DEQueue->length+1);\
        /*se aumentan tail y length para reflejar que se añadirá un elemento, se pone el dato deseado en el espacio correcto*/\
        DEQueue->tail ++;\
        DEQueue->length ++;\
        DEQueue->posicion[DEQueue->tail] = data;\
    }\
    void DEQueue_##TYPE##_dequeue_head( D_E_Queue_##TYPE* DEQueue){\
        /*Si la cola está vacía, no se puede desencolar , no se hace nada más. si sólo había un elemento, se restablecen los valores default, y si no es ninguna, se mueven los elementos para desencolar*/\
        if(DEQueue_##TYPE##_is_empty(DEQueue)){\
            printf("la cola está vacía");\
            return;\
        }\
        if(DEQueue->length==1){\
            DEQueue->head =-1;\
            DEQueue->tail = -1;\
            DEQueue->length=0;\
            return;\
        }\
        /*se recorren los elemenots y se cambian length y tail, quitando el elemento en 0 y preservando la estructura de la cola correctamente*/\
        for(int i = 0; i<DEQueue->length-1;i++){\
            DEQueue->posicion[i]=DEQueue->posicion[i+1];\
        }\
        DEQueue->length--;\
        DEQueue->tail--;\
    }\
    void DEQueue_##TYPE##_dequeue_tail( D_E_Queue_##TYPE* DEQueue){\
        /*Si la cola está vacía, no se puede desencolar , no se hace nada más. si sólo había un elemento, se restablecen los valores default, y si no es ninguna, se mueven los elementos para desencolar*/\
        if(DEQueue_##TYPE##_is_empty(DEQueue)){\
            printf("la cola está vacía");\
            return;\
        }\
        if(DEQueue->length==1){\
            DEQueue->head =-1;\
            DEQueue->tail = -1;\
            DEQueue->length=0;\
            return;\
        }\
        /*se cambian length y tail, quitando el elemento en tail y preservando la estructura de la cola correctamente*/\
        DEQueue->length--;\
        DEQueue->tail--;\
    }\
    TYPE DEQueue_##TYPE##_first(const D_E_Queue_##TYPE* DEQueue){\
        /*si la cola está vacía se imprime un error y se manda el '0' como error con el tipo apropiado. si no está vacía, se retorna el primer dato (posición 0)*/\
        if(!DEQueue_##TYPE##_is_empty(DEQueue)){\
            printf("cola vacía");\
            return (TYPE)0;\
        }\
        return DEQueue->posicion[0];\
    }\
    TYPE DEQueue_##TYPE##_last(const D_E_Queue_##TYPE* DEQueue){\
        /*si la cola está vacía se imprime un error y se manda el '0' como error con el tipo apropiado. si no está vacía, se retorna el último dato (posición tail)*/\
        if(!DEQueue_##TYPE##_is_empty(DEQueue)){\
            printf("cola vacía");\
            return (TYPE)0;\
        }\
        return DEQueue->posicion[DEQueue->tail];\
    }\
    bool DEQueue_##TYPE##_is_empty(const D_E_Queue_##TYPE* DEQueue){\
        /*si la longitud es 0, retorna verdad, si no, retorna falso*/\
        return DEQueue->length==0;\
    }\
    void DEQueue_##TYPE##_empty(const D_E_Queue_##TYPE* DEQueue){\
        /*se restablecen los valores default a como si estuviera vacía.*/\
        DEQueue->head =-1;\
            DEQueue->tail = -1;\
            DEQueue->length=0;\
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