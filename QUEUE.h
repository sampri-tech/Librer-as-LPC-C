#ifndef QUEUE_H
#define QUEUE_H

#include<stddef.h>

typedef struct NodeQueue Node;
typedef struct Queue Queue;

/**
 * @brief Crear una cola nueva
 * 
 * @return Queue* puntero a la cola recién creada, o NULL si el malloc falla.
 */
Queue *NewQueue(void);

/**
 * @brief Encolar un elemento a la cola en la última posición.
 * 
 * @param queue La cola en donde se va a encolar el elemento.
 * @param element el elemento que va a ser encolado.
 */
void Enqueue(Queue *queue, void *element);

/**
 * @brief Desencolar el elemento de la primera posición.
 * 
 * @param queue La cola en donde se va a desencolar el elemento.
 */
void *Dequeue(Queue *queue);

/**
 * @brief Ver el elemento en primera posición.
 * 
 * @param queue Cola donde se encuentra el elemento.
 * @return void* Elemento que se encuentra en la primera posición, NULL si es vacío.
 */
void *PeekFirst(const Queue *queue);

/**
 * @brief Verifica si la cola esta vacia.
 * 
 * @param queue Cola que se va a verificar.
 * @return int 1 si la cola esta vacía, sino 0.
 */
int IsEmpty(const Queue *queue);

/**
 * @brief Obtener el tamaño de la cola.
 * 
 * @param queue Cola a consultar.
 * @return size_t El tamaño de la cola.
 */
size_t GetSize(const Queue *queue);

/**
 * @brief Vaciar la cola.
 * 
 * @param queue Cola a vacíar.
 */
void ClearQueue(Queue *queue);

/**
 * @brief Destruir cola.
 * 
 * @param queue Cola a destruir.
 */
void DestroyQueue(Queue *queue);

#endif