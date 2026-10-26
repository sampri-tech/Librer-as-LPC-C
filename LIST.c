#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LIST.h"


struct NodeList {
    void *element; // elemento que se guarda en el nodo
    struct NodeList *prev; // Nodo anterior
    struct NodeList *next; // Nodo siguiente
};

struct List {
    size_t size; // tamaño de la lista
    size_t eSize; // tamaño de los elementos que se van a guardar
    NodeL *head; // puntero al primer nodo de la lista
    NodeL *tail; // puntero al ultimo nodo de la lista
};

List *NewList(void){
    List *list;

    list = (List *)malloc(sizeof(List));
    if(list == NULL){
        fprintf(stderr, "Error: fallo de memoria al crear la lista.\n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->eSize = 0;
    return list;
}

List *CopyList(const List *list){
    const NodeL *current;
    NodeL *new;
    List *newList;
    void *copy;

    if(list == NULL) return NULL;

    newList = (List *)malloc(sizeof(List));
    if(newList == NULL) return NULL;

    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    newList->eSize = list->eSize;

    current = list->head;
    while (current != NULL){
        copy = malloc(list->eSize);
        new  = (NodeL *)malloc(sizeof(NodeL));

        if(copy == NULL || new == NULL){
            free(copy);          /* free(NULL) es válido */
            free(new);
            while(newList->head != NULL){
                new = newList->head;
                newList->head = new->next;
                free(new->element);
                free(new);
            }
            free(newList);
            fprintf(stderr, "fallo de memoria al copiar la lista.\n");
            return NULL;
        }

        memcpy(copy, current->element, list->eSize);
        new->element = copy;
        new->next = NULL;
        new->prev = newList->tail;

        if(newList->head == NULL){
            newList->head = new;
        }else{
            newList->tail->next = new;
        }

        newList->tail = new;
        newList->size++;
        current = current->next;
    }

    return newList;
}

List *ConcatList(const List *list1, const List *list2){
    const List *srcs[2];
    List *newList;
    const NodeL *current;
    NodeL  *new, *prev;
    void *copy;
    size_t i;

    if(list1 == NULL && list2 == NULL) return NULL;
    if((list1 != NULL) && (list2 != NULL) && (list1->eSize != 0) && (list2->eSize != 0) && (list1->eSize != list2->eSize)){
        fprintf(stderr, "Error: las listas tienen elementos de distinto tamaño, por lo que no se pueden concatenar.\n");
        return NULL;
    }

    newList = (List *)malloc(sizeof(List));
    if(newList == NULL){
        fprintf(stderr, "Error: fallo de memoria al crear la nueva lista para concatenar.\n");
        return NULL;
    }

    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    if((list1 != NULL) && (list1->eSize != 0)){
        newList->eSize = list1->eSize;
    }else if(list2 != NULL){
        newList->eSize = list2->eSize;
    }else{
        newList->eSize = 0;
    }

    srcs[0] = list1;
    srcs[1] = list2;
    prev   = NULL;

    for(i = 0; i < 2; i++){
        if(srcs[i] != NULL){
            current = srcs[i]->head;
            while(current != NULL){
                copy = malloc(newList->eSize);
                new = (NodeL *)malloc(sizeof(NodeL));
                if(copy == NULL || new == NULL){
                    free(copy);
                    free(new);

                    while(newList->head != NULL){
                        new = newList->head;
                        newList->head = new->next;
                        free(new->element);
                        free(new);
                    }
                    free(newList);
                    fprintf(stderr, "Error: fallo de memoria al copiar uno de los nodo.\n");
                    return NULL;
                }

                memcpy(copy, current->element, newList->eSize);

                new->element = copy;
                new->prev = prev;
                new->next = NULL;

                if(prev != NULL){
                    prev->next = new;
                }else{
                    newList->head = new;
                }

                newList->tail = new;
                prev = new;
                newList->size++;

                current = current->next;
            }
        }
    }

    return newList;
}

List *SearchElement(const List *list, void *ele, int (*cmp)(const void *, const void *)){
    List *newlist;
    const NodeL *current;
    NodeL *new, *prev;
    void *copy;

    if(list == NULL) return NULL;
    
    if(ele == NULL || cmp == NULL){
        fprintf(stderr, "Error: elemento o comparador no hallados.\n");
        return NULL;
    }

    newlist = (List *)malloc(sizeof(List));
    if(newlist == NULL){
        fprintf(stderr, "Error: fallo de memoria al crear una lista.\n");
        return NULL;
    }

    newlist->head = NULL;
    newlist->tail = NULL;
    newlist->size = 0;
    newlist->eSize = list->eSize;

    prev = NULL;
    current = list->head;
    while(current != NULL){
        if(cmp(current->element, ele) != 0){
            copy = malloc(newlist->eSize);
            new  = (NodeL *)malloc(sizeof(NodeL));

            if(copy == NULL || new == NULL){
                free(copy);
                free(new);
                while(newlist->head != NULL){
                    new = newlist->head;
                    newlist->head = new->next;
                    free(new->element);
                    free(new);
                }
                free(newlist);
                fprintf(stderr, "Error: fallo de memoria al copiar uno de los nodos.\n");
                return NULL;
            }

            memcpy(copy, current->element, newlist->eSize);

            new->element = copy;
            new->prev = prev;
            new->next = NULL;

            if(prev != NULL){
                prev->next = new;
            }else{
                newlist->head = new;
            }

            newlist->tail = new;
            prev = new;
            newlist->size++;
        }

        current = current->next;
    }

    return newlist;
}

const NodeL *GetHead(const List *list){
    return (list != NULL) ? list->head : NULL;
}

const NodeL *GetTail(const List *list){
    return (list != NULL) ? list->tail : NULL;
}

const NodeL *GetPrev(const NodeL *node){
    return (node != NULL) ? node->prev : NULL;
}

const NodeL *GetNext(const NodeL *node){
    return (node != NULL) ? node->next : NULL;
}

size_t GetSize(const List *list){
    return (list != NULL) ? list->size : 0;
}

void *GetElement(const NodeL *node){
    return (node != NULL) ? node->element : NULL;
}

int IsEmpty(const List *list){
    return (list == NULL || list->head == NULL) ? 1 : 0;
}

void Add(List *list, void *elem, size_t elemSize, size_t pos){
    NodeL *new, *current;
    size_t i;
    void *save;


    if((list != NULL) && (pos <= list->size) && (elemSize > 0) && (elem != NULL)){
        if((list->eSize != 0) && (list->eSize != elemSize)){
            fprintf(stderr, "Error: el tamaño del elemento no coincide con el de la lista.\n");
        }else{
            save = malloc(elemSize);
            if(save != NULL){
                new = (NodeL *)malloc(sizeof(NodeL));
                if (new != NULL ){
                    memcpy(save, elem, elemSize);
                    new->element = save;
                    new->prev = NULL;
                    new->next = NULL;
                    if(pos == 0){
                        new->next = list->head;
                        if(list->head == NULL){
                            list->tail = new;
                        }else{
                            list->head->prev = new;
                        }
                        list->head = new;
                    }else if(pos == list->size){
                        new->prev = list->tail;
                        list->tail->next = new;
                        list->tail  = new;
                    }else{
                        current = list->head;
                        for( i = 0; i < pos - 1; i++){
                            current = current->next;
                        }
                        new->prev = current;
                        new->next = current->next;
                        current->next->prev = new;
                        current->next = new;
                    }

                    list->size++;
                    list->eSize = elemSize;
                }else{
                    fprintf(stderr, "Error: fallo de memoria al agregar un nuevo elemento.\n");
                    free(save);
                }
            }else{
                fprintf(stderr, "Error: fallo de memoria al agregar un nuevo elemento.\n");
            }
        }
    }
}

void Delete(List *list, size_t pos){
    NodeL *current;
    size_t i;

    if(list != NULL){
        if((pos < list->size)){
            if(pos == 0){
                current = list->head;
                list->head = list->head->next;
                if (list->head != NULL) {
                    list->head->prev = NULL;
                } else {
                    list->tail = NULL;
                }
            }else if(pos == list->size - 1){
                current = list->tail;
                list->tail = list->tail->prev;
                list->tail->next = NULL;
            }else{
                current = list->head;
                for( i = 0; i < pos; i++){
                    current = current->next;
                }
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            free(current->element);
            free(current);
            list->size -= 1;
        }else{
            fprintf(stderr, "Error: posición fuera de rango.\n");
        }
    }
}

void *SearchInPosition(const List *list, size_t pos){
    size_t i;
    NodeL *current;

    if ((list == NULL) || (list->head == NULL) || (pos >= list->size)) return NULL;

    current = list->head;
    for( i = 0; i < pos; i++){
        current = current->next;
    }

    return current->element;
}

void SplitList(List *list, List *list1, List *list2){
    NodeL *current, *next, *cut, *splitted;
    size_t mid, i;

    if(list != NULL){
        if((list1 != NULL) && (list2 != NULL)){
            if((list1 != list) && (list2 != list) && (list1 != list2)){
                current = list1->head;
                while (current != NULL){
                    next = current->next;
                    free(current->element);
                    free(current);
                    current = next;
                }
                list1->head = NULL;
                list1->tail = NULL;
                list1->size = 0;

                current = list2->head;
                while (current != NULL){
                    next = current->next;
                    free(current->element);
                    free(current);
                    current = next;
                }
                list2->head = NULL;
                list2->tail = NULL;
                list2->size = 0;

                if(list->eSize != 0){
                    list1->eSize = list->eSize;
                    list2->eSize = list->eSize;
                }
                if(list->size > 0){
                    mid = list->size / 2;
                    if((list->size % 2) != 0) mid++;

                    cut = list->head;
                    for(i = 0; i < mid - 1; i++){
                        cut = cut->next;
                    }

                    splitted = cut->next;
                    cut->next = NULL;

                    list1->head = list->head;
                    list1->tail = cut;
                    list1->size = mid;

                    list2->head = splitted;
                    list2->size = list->size - mid;
                    if(splitted != NULL){
                        splitted->prev = NULL;
                        list2->tail = list->tail;
                    }else{
                        list2->tail = NULL;
                    }
                    
                    list->head = NULL;
                    list->tail = NULL;
                    list->size = 0;
                }
            }else{
                fprintf(stderr, "Error: las listas destinos deben ser diferentes a las de origen y entre si.\n");
            }
        }else{
            fprintf(stderr, "Error: lista(s) destino(s) nula(s).\n");
        }
    }else{
        fprintf(stderr, "Error: la lista de origen es nula.\n");
    }
}

void MergeSortList(List *list, int (*cmp)(const void *, const void *)){
    size_t size, i;
    NodeL *current, *next, *left, *right, *tail, *rest;
    NodeL *merged, *mergedTail, *auxl, *auxr, *pick, *restNext;

    if((list != NULL) && (list->head != NULL) && (list->head->next != NULL) && (cmp != NULL)){
        for(size = 1; size < list->size; size *= 2){

            left = list->head;
            tail = NULL;
            list->head = NULL;

            while(left != NULL){

                current = left;
                for(i = 1; i < size && current->next != NULL; i++){
                    current = current->next;
                }
                right = current->next;
                current->next = NULL;

                current = right;
                if(current != NULL){
                    for(i = 1; i < size && current->next != NULL; i++){
                        current = current->next;
                    }
                }

                next = NULL;
                if(current != NULL){
                    if(current->next != NULL){
                        next = current->next;
                        current->next = NULL;
                    }
                }

                merged = NULL;
                mergedTail = NULL;
                auxl = left;
                auxr = right;

                while(auxl != NULL && auxr != NULL){
                    if(cmp(auxl->element, auxr->element) > 0){
                        pick = auxl;
                        auxl = auxl->next;
                    }else{
                        pick = auxr;
                        auxr = auxr->next;
                    }
                    pick->next = NULL;
                    pick->prev = NULL;
                    if(merged == NULL){
                        merged = pick;
                        mergedTail = pick;
                    }else{
                        mergedTail->next = pick;
                        pick->prev = mergedTail;
                        mergedTail = pick;
                    }
                }

                rest = (auxl != NULL) ? auxl : auxr;
                while(rest != NULL){
                    restNext = rest->next;
                    rest->next = NULL;
                    rest->prev = mergedTail;

                    if(merged == NULL){
                        merged = rest;
                        mergedTail = rest;
                    }else{
                        mergedTail->next = rest;
                        mergedTail = rest;
                    }
                    rest = restNext;
                }

                if(list->head == NULL){
                    list->head = merged;
                }else{
                    tail->next = merged;
                    merged->prev = tail;
                }

                if(mergedTail != NULL){
                    tail = mergedTail;
                }

                left = next;
            }
            list->tail = tail;
            if(list->head != NULL) list->head->prev = NULL;
        }
    }
}

void ClearList(List *list){
    NodeL *current, *next;

    if(list != NULL){
        current = list->head;
        while (current != NULL){
            next = current->next;
            free(current->element);
            free(current);
            current = next;
        }
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}

void DestroyList(List *list){
    NodeL *current, *next;

    if(list != NULL){
        current = list->head;
        while (current != NULL){
            next = current->next;
            free(current->element);
            free(current);
            current = next;
        }
        free(list);
    }
}