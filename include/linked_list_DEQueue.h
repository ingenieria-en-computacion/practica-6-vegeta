#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// ----------------------------
// Macro para declarar estructuras y prototipos
// ----------------------------

#define DECLARE_LINKED_LIST(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
    } Node_##TYPE; \
    /*Operaciones de los nodos*/ \
    Node_##TYPE* node_##TYPE##__create(TYPE);\
    Node_##TYPE* node_##TYPE##_destroy(Node_##TYPE*);\
    \
    typedef struct { \
        Node_##TYPE* head; \
        Node_##TYPE* tail; \
        size_t length; \
    } List_##TYPE; \
    \
    /*Operaciones de las listas ligadas*/ \
    List_##TYPE* list_##TYPE##_create(void); \
    void list_##TYPE##_destroy(List_##TYPE* list); \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos); \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data); \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos); \
    bool list_##TYPE##_get(const List_##TYPE* list, size_t pos, TYPE* out); \
    size_t list_##TYPE##_length(const List_##TYPE* list); \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE));\
    \
    /*Operaciones de las Colas con dos finales (DEQueue o Double ended queue) implementadas como lista ligada*/\
    List_##TYPE* DEQueue_##TYPE##_create(void); \
    void DEQueue_##TYPE##_destroy( List_##TYPE* DEQueue);\
    void DEQueue_##TYPE##_print(const List_##TYPE* DEQueue, void (*print_fn)(TYPE));\
    void DEQueue_##TYPE##_enqueue_head( List_##TYPE* DEQueue, TYPE data);\
    void DEQueue_##TYPE##_enqueue_tail( List_##TYPE* DEQueue, TYPE data);\
    void DEQueue_##TYPE##_dequeue_head( List_##TYPE* DEQueue);\
    void DEQueue_##TYPE##_dequeue_tail( List_##TYPE* DEQueue);\
    TYPE DEQueue_##TYPE##_first(const List_##TYPE* DEQueue);\
    TYPE DEQueue_##TYPE##_last(const List_##TYPE* DEQueue);\
    bool DEQueue_##TYPE##_is_empty(const List_##TYPE* DEQueue);\
    void DEQueue_##TYPE##_empty(const List_##TYPE* DEQueue);\
// ----------------------------
// Macro para implementación
// ----------------------------
#define IMPLEMENT_LINKED_LIST(TYPE) \
    Node_##TYPE* node_##TYPE##_create(TYPE data){\
        Node_##TYPE* new_node = (Node_##TYPE*)malloc(sizeof(Node_##TYPE)); \
        new_node->data = data;\
        new_node->next = NULL;\
        return new_node;\
    }\
    \
    Node_##TYPE* node_##TYPE##_destroy(Node_##TYPE *node){\
        if(node->next ==NULL){\
            free(node);\
            return NULL;\
        }\
        return node;\
    }\
    List_##TYPE* list_##TYPE##_create(void) { \
        List_##TYPE* list = malloc(sizeof(List_##TYPE)); \
        if (!list) return NULL; \
        list->head = list->tail = NULL; \
        list->length = 0; \
        return list; \
    } \
    \
    void list_##TYPE##_destroy(List_##TYPE* list) { \
        if (!list) return; \
        Node_##TYPE* current = list->head; \
        while (current) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } \
        free(list); \
    } \
    \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos) { \
        if (!list || pos > list->length) return false; \
        \
        Node_##TYPE* new_node = node_##TYPE##_create(data); \
        if (!new_node) return false; \
        \
        if (pos == 0) { \
            new_node->next = list->head; \
            list->head = new_node; \
            if (!list->tail) list->tail = new_node; \
        } else if (pos == list->length) { \
            new_node->next = NULL; \
            list->tail->next = new_node; \
            list->tail = new_node; \
        } else { \
            Node_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            new_node->next = current->next; \
            current->next = new_node; \
        } \
        \
        list->length++; \
        return true; \
    } \
    \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data) { \
        return list_##TYPE##_insert(list, data, list->length); \
    } \
    \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos) { \
        if (!list || pos >= list->length) return false; \
        \
        Node_##TYPE* to_delete = NULL; \
        \
        if (pos == 0) { \
            to_delete = list->head; \
            list->head = list->head->next; \
            if (!list->head) list->tail = NULL; \
        } else { \
            Node_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            to_delete = current->next; \
            current->next = to_delete->next; \
            if (pos == list->length - 1) { \
                list->tail = current; \
            } \
        } \
        \
        free(to_delete); \
        list->length--; \
        return true; \
    } \
    \
    bool list_##TYPE##_get(const List_##TYPE* list, size_t pos, TYPE* out) { \
        if (!list || !out || pos >= list->length) return false; \
        \
        Node_##TYPE* current = list->head; \
        for (size_t i = 0; i < pos; ++i) { \
            current = current->next; \
        } \
        \
        *out = current->data; \
        return true; \
    } \
    \
    size_t list_##TYPE##_length(const List_##TYPE* list) { \
        return list ? list->length : 0; \
    } \
    \
    bool list_##TYPE##_is_empty(const List_##TYPE* list) { \
        return list ? list->length == 0 : true; \
    } \
    \
    void list_##TYPE##_clear(List_##TYPE* list) { \
        if (!list) return; \
        \
        Node_##TYPE* current = list->head; \
        while (current) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } \
        \
        list->head = list->tail = NULL; \
        list->length = 0; \
    } \
    \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE)) { \
        if (!list || !print_fn) return; \
        \
        printf("["); \
        Node_##TYPE* current = list->head; \
        while (current) { \
            print_fn(current->data); \
            if (current->next) printf(", "); \
            current = current->next; \
        } \
        printf("]\n"); \
    } \
    \
    bool list_##TYPE##_contains(const List_##TYPE* list, TYPE data) { \
        if (!list) return false; \
        \
        Node_##TYPE* current = list->head; \
        while (current) { \
            if (current->data == data) { \
                return true; \
            } \
            current = current->next; \
        } \
        \
        return false; \
    } \
    \
    bool list_##TYPE##_remove(List_##TYPE* list, TYPE data) { \
        if (!list) return false; \
        \
        Node_##TYPE* prev = NULL; \
        Node_##TYPE* current = list->head; \
        \
        while (current) { \
            if (current->data == data) { \
                if (prev) { \
                    prev->next = current->next; \
                    if (!current->next) { \
                        list->tail = prev; \
                    } \
                } else { \
                    list->head = current->next; \
                    if (!list->head) { \
                        list->tail = NULL; \
                    } \
                } \
                \
                free(current); \
                list->length--; \
                return true; \
            } \
            \
            prev = current; \
            current = current->next; \
        } \
        \
        return false; \
    }\
    \
    List_##TYPE* DEQueue_##TYPE##_create(void){ \
        return list_##TYPE##_create();\
    }\
    void DEQueue_##TYPE##_destroy( List_##TYPE* DEQueue){\
        list_##TYPE##_destroy(DEQueue);\
    }\
    void DEQueue_##TYPE##_print(const List_##TYPE* DEQueue, void (*print_fn)(TYPE)){\
        list_##TYPE##_print(DEQueue, print_fn);\
    }\
    void DEQueue_##TYPE##_enqueue_head( List_##TYPE* DEQueue, TYPE data ){\
        list_##TYPE##_insert(DEQueue, data, 0);\
        /*Para encolar en la cola doble sólo hay que empezar con una lista ligada,e insertar al inicio (pos 0)*/ \
    }\
    void DEQueue_##TYPE##_enqueue_tail( List_##TYPE* DEQueue, TYPE data ){\
        list_##TYPE##_append(DEQueue, data);\
        /*Para encolar en la cola doble sólo hay que empezar con una lista ligada, e insertar al final (append) */ \
   }\
    void DEQueue_##TYPE##_dequeue_head( List_##TYPE* DEQueue){\
        /* Para desencolar sólo hay que remover el nodo en head (posicion 0 de la lista)*/\
        list_##TYPE##_remove_at(DEQueue, 0);\
    }\
    void DEQueue_##TYPE##_dequeue_tail( List_##TYPE* DEQueue){\
        /* Para desencolar al final sólo hay que remover el nodo en tail (posicion length-1 de la lista)*/\
        list_##TYPE##_remove_at(DEQueue, DEQueue->length-1);\
    }\
    TYPE DEQueue_##TYPE##_first(const List_##TYPE* DEQueue){\
        /*Para leer el primer elemento, sólo hay que usar get en head (posición 0)*/ \
        TYPE out;\
        list_##TYPE##_get(DEQueue, 0 , &out);\
        return out;\
    }\
    TYPE DEQueue_##TYPE##_last(const List_##TYPE* DEQueue){\
        /*Para leer el último elemento, sólo hay que usar get en tail( última posición, length-1)*/ \
        TYPE out;\
        list_##TYPE##_get(DEQueue, DEQueue->length-1 , &out);\
        return out;\
    }\
    bool DEQueue_##TYPE##_is_empty(const List_##TYPE* DEQueue){\
        /* preguntar por la longitud de la lista, si es 0, la lista está vacía*/\
        return DEQueue->length==0;\
    }\
    void DEQueue_##TYPE##_empty( List_##TYPE* DEQueue){\
        /* el código de destruir una lista primero la vacía y luego la libera. si sólo quiere vaciarse, se puede copiar el código pero no destruirla una vez es vaciada*/ \
        if (!DEQueue) return; \
        Node_##TYPE* current = DEQueue->head; \
        while (current) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } \
    }\

// ----------------------------
// Declaración para tipos concretos
// ----------------------------
DECLARE_LINKED_LIST(int)
DECLARE_LINKED_LIST(char)
DECLARE_LINKED_LIST(float)

// ----------------------------
// Implementación para tipos concretos
// ----------------------------
#ifdef LINKED_LIST_IMPLEMENTATION
IMPLEMENT_LINKED_LIST(int)
IMPLEMENT_LINKED_LIST(char)
IMPLEMENT_LINKED_LIST(float)
#endif
