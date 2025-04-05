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
    /*Operaciones de las Colas circulares (CircularQueue) implementadas como lista ligada*/\
    List_##TYPE* CircularQueue_##TYPE##_create(void); \
    void CircularQueue_##TYPE##_destroy( List_##TYPE* CircularQueue);\
    void CircularQueue_##TYPE##_print(const List_##TYPE* CircularQueue, void (*print_fn)(TYPE));\
    void CircularQueue_##TYPE##_enqueue( List_##TYPE* CircularQueue, TYPE data);\
    void CircularQueue_##TYPE##_dequeue( List_##TYPE* CircularQueue);\
    TYPE CircularQueue_##TYPE##_first(const List_##TYPE* CircularQueue);\
    TYPE CircularQueue_##TYPE##_last(const List_##TYPE* CircularQueue);\
    bool CircularQueue_##TYPE##_is_empty(const List_##TYPE* CircularQueue);\
    void CircularQueue_##TYPE##_empty(const List_##TYPE* CircularQueue);\
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
    List_##TYPE* CircularQueue_##TYPE##_create(void){ \
        return list_##TYPE##_create();\
    }\
    void CircularQueue_##TYPE##_destroy( List_##TYPE* CircularQueue){\
        list_##TYPE##_destroy(CircularQueue);\
    }\
    void CircularQueue_##TYPE##_print(const List_##TYPE* CircularQueue, void (*print_fn)(TYPE)){\
        list_##TYPE##_print(CircularQueue, print_fn);\
    }\
    void CircularQueue_##TYPE##_enqueue( List_##TYPE* CircularQueue, TYPE data ){\
        list_##TYPE##_append(CircularQueue, data);\
        /*Para encolar en la cola circular sólo hay que empezar con una lista ligada, \
        insertar al final (append) y volverla circular apuntando al siguiente de tail en head*/ \
        if (CircularQueue->tail) CircularQueue->tail->next = CircularQueue->head; \
    }\
    void CircularQueue_##TYPE##_dequeue( List_##TYPE* CircularQueue){\
        /* Para desencolar sólo hay que remover el nodo en head (posicion 0 de la lista), y conservar la circularidad de nuevo apuntando el siguiente de tail a head*/\
        list_##TYPE##_remove_at(CircularQueue, 0);\
        if (CircularQueue->tail) CircularQueue->tail->next = CircularQueue->head; \
    }\
    TYPE CircularQueue_##TYPE##_first(const List_##TYPE* CircularQueue){\
        /*Para leer el primer elemento, sólo hay que usar get en head (posición 0)*/ \
        TYPE out;\
        list_##TYPE##_get(CircularQueue, 0 , &out);\
        return out;\
    }\
    TYPE CircularQueue_##TYPE##_last(const List_##TYPE* CircularQueue){\
        /*Para leer el último elemento, sólo hay que usar get en tail( última posición, length-1)*/ \
        TYPE out;\
        list_##TYPE##_get(CircularQueue, CircularQueue->length-1 , &out);\
        return out;\
    }\
    bool CircularQueue_##TYPE##_is_empty(const List_##TYPE* CircularQueue){\
        /* preguntar por la longitud de la lista, si es 0, la lista está vacía*/\
        return CircularQueue->length==0;\
    }\
    void CircularQueue_##TYPE##_empty( List_##TYPE* CircularQueue){\
        /* el código de destruir una lista primero la vacía y luego la libera. si sólo quiere vaciarse, se puede copiar el código pero no destruirla una vez es vaciada*/ \
        if (!CircularQueue) return; \
        Node_##TYPE* current = CircularQueue->head; \
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
