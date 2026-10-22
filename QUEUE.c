#include<stdio.h>
#include<stdlib.h>
#include"QUEUE.h"

struct NodeQueue{
    void *element; // Elemento guardado en el nodo
    struct NodeQueue *next; // Puntero al siguiente nodo
};

struct Queue{
    size_t size; // Tamaño de la cola
    Node *first; // puntero al primer nodo de la cola
    Node *last; // puntero al ultimo nodo de la cola
};

Queue *NewQueue(void){
    Queue *queue;

    queue = (Queue *)malloc(sizeof(Queue));
    if(queue != NULL){
        queue->first = NULL;
        queue->last = NULL;
        queue->size = 0;
    }

    return queue;
}

void Enqueue(Queue *queue, void *element){
    Node *new;

    if(queue != NULL){
        new = (Node *)malloc(sizeof(Node));
        if(new != NULL){
            new->element = element;
            new->next = NULL;
            if(queue->first == NULL){
                queue->first = new;
                queue->last = new;
            }else{
                queue->last->next = new;
                queue->last = queue->last->next;
            }
            queue->size++;
        } 
    }
}

void *Dequeue(Queue *queue){
    Node *aux;

    if(queue != NULL){
        if((queue->size != 0) && (queue->first != NULL)){
            aux = queue->first;
            queue->first = queue->first->next;
            free(aux);
            queue->size--;
        }
    }
}

void *PeekFirst(const Queue *queue){
    return (queue != NULL && queue->first != NULL) ? queue->first->element : NULL;
}

int IsEmpty(const Queue *queue){
    return (queue == NULL || queue->first == NULL) ? 1 : 0;
}

size_t GetSize(const Queue *queue){
    return (queue != NULL) ? queue->size : 0;
}

void ClearQueue(Queue *queue){
    Node *aux;

    if(queue != NULL){
        while (queue->first != NULL){
            aux = queue->first->next;
            free(queue->first);
            queue->first = aux;
        }
        
        queue->first = NULL;
        queue->last = NULL;
        queue->size = 0;
    }
}

void DestroyQueue(Queue *queue){
    Node *aux;

    if(queue != NULL){
        while (queue->first != NULL){
            aux = queue->first->next;
            free(queue->first);
            queue->first = aux;
        }
        free(queue);
    }
}
