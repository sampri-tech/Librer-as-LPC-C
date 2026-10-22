#include<stdio.h>
#include<stdlib.h>
#include"LIST.h"


struct NodeList {
    void *element; // elemento que se guarda en el nodo
    struct NodeList *prev; // Nodo anterior
    struct NodeList *next; // Nodo siguiente
};

struct List {
    size_t size; // tamaño de la lista
    Node *head; // puntero al primer nodo de la lista
    Node *tail; // puntero al ultimo nodo de la lista
};

List *NewList(void){
    List *list;

    list = (List *)malloc(sizeof(List));
    if(list != NULL){
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
    return list;
}

List *CopyList(const List *list){
    const Node *current;
    Node *new;
    List *newList;

    if(list == NULL) return NULL;

    newList = NewList();
    if(newList == NULL) return NULL;

    current = list->head;
    while (current != NULL){
        new = (Node *)malloc(sizeof(Node));
        if(new == NULL){
            ClearList(newList);
            free(newList);
            return NULL;
        }
        new->element = current->element;
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
    List *newList;
    const Node *current;

    if(list1 == NULL && list2 == NULL) return NULL;
    newList = NewList();
    if(newList == NULL) return NULL;

    if(list1 != NULL){
        current = list1->head;
        while(current != NULL){
            Add(newList, current->element, GetSize(newList));
            current = current->next;
        }
    }

    if(list2 != NULL){
        current = list2->head;
        while(current != NULL){
            Add(newList, current->element, GetSize(newList));
            current = current->next;
        }
    }

    return newList;
}

List *SearchElement(const List *list, void *ele){
    List *newlist;
    const Node *current;

    if(list == NULL) return NULL;

    newlist = NewList();
    current = list->head;
    while(current != NULL){
        if(current->element == ele){
            Add(newlist, current->element, GetSize(newlist));
        }
        current = current->next;
    }
    return newlist;
}

const Node *GetHead(const List *list){
    return (list != NULL) ? list->head : NULL;
}

const Node *GetTail(const List *list){
    return (list != NULL) ? list->tail : NULL;
}

const Node *GetPrev(const Node *node){
    return (node != NULL) ? node->prev : NULL;
}

const Node *GetNext(const Node *node){
    return (node != NULL) ? node->next : NULL;
}

size_t GetSize(const List *list){
    return (list != NULL) ? list->size : 0;
}

void *GetElement(const Node *node){
    return (node != NULL) ? node->element : NULL;
}

int IsEmpty(const List *list){
    return (list == NULL || list->head == NULL) ? 1 : 0;
}

void Add(List *list, void *ele, size_t pos){
    Node *new, *current;
    size_t i;

    if(list != NULL && pos <= list->size){
        new = (Node *)malloc(sizeof(Node));
        if (new != NULL){
            new->element = ele;
            if(pos == 0){
                if(list->head == NULL){
                    new->next = NULL;
                    list->tail = new;
                }else{
                    list->head->prev = new;
                    new->next = list->head;
                }
                new->prev = NULL;
                list->head = new;
            }else if(pos == list->size){
                list->tail->next = new;
                new->prev = list->tail;
                new->next = NULL;
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
            list->size += 1;
        }
    }
}

void Delete(List *list, size_t pos){
    Node *current;
    size_t i;

    if(list != NULL && pos < list->size){
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
        free(current);
        list->size -= 1;
    }
}

void *SearchPosition(const List *list, size_t pos){
    size_t i;
    Node *current;

    if (IsEmpty(list) || pos >= list->size) return NULL;

    current = list->head;
    for( i = 0; i < pos; i++){
        current = current->next;
    }

    return current->element;
}

void SplitList(List *list, List **list1, List **list2){
    Node *current, *next, *splitNode;
    size_t mid, i;

    if(list != NULL){

        if(*list1 != NULL){
            current = (*list1)->head;
            while (current != NULL){
                next = current->next;
                free(current);
                current = next;
            }
            (*list1)->head = NULL;
            (*list1)->tail = NULL;
            (*list1)->size = 0;
        }

        if(*list2 != NULL){
            current = (*list2)->head;
            while (current != NULL){
                next = current->next;
                free(current);
                current = next;
            }
            (*list2)->head = NULL;
            (*list2)->tail = NULL;
            (*list2)->size = 0;
        }

        mid = list->size / 2;

        if((list->size % 2) != 0) mid++;

        splitNode = list->head;
        for(i = 0; i < mid - 1; i++){
            splitNode = splitNode->next;
        }

        if(*list1 == NULL){
            *list1 = (List *)malloc(sizeof(List));
        }
        if(*list1 != NULL){
            (*list1)->head = list->head;
            (*list1)->tail = splitNode;
            (*list1)->size = mid;
            if((*list1)->tail != NULL) (*list1)->tail->next = NULL;
        }

        if(*list2 == NULL){
            *list2 = (List *)malloc(sizeof(List));
        }
        if(*list2 != NULL){
            (*list2)->head = splitNode->next;
            (*list2)->tail = list->tail;
            (*list2)->size = list->size - mid;
            if((*list2)->head != NULL) (*list2)->head->prev = NULL;
        }

        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}

void MergeSortList(List *list, int (*cmp)(const void *, const void *)){
    size_t size, i;
    Node *current, *next, *left, *right, *tail, *rest;
    Node *merged, *mergedTail, *auxl, *auxr, *pick, *restNext;

    if((list != NULL) && (list->head != NULL) && (list->head->next != NULL)){
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
    Node *current, *next;

    if(list != NULL){
        current = list->head;
        while (current != NULL){
            next = current->next;
            free(current);
            current = next;
        }
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}

void DestroyList(List *list){
    Node *current, *next;

    if(list != NULL){
        current = list->head;
        while (current != NULL){
            next = current->next;
            free(current);
            current = next;
        }
        free(list);
    }
}