#ifndef STACK_H
#define STACK_H

#include<stddef.h>

typedef struct NodeStack Node;
typedef struct Stack Stack;

/**
 * @brief Crear una pila nueva.
 * 
 * @return Stack* Puntero a la pila creada, o NULL si el malloc falla.
 */
Stack *NewStack(void);

/**
 * @brief Apilar un elemento en la primera posición de una pila.
 * 
 * @param stack Pila donde a apilar.
 * @param element elemento a apilar.
 */
void Push(Stack *stack, void *element);

/**
 * @brief Desapilar el primer elemento de una pila.
 * 
 * @param stack Pila a desapilar.
 */
void *Pop(Stack *stack);

/**
 * @brief Ver elemento en la primera pocisión.
 * 
 * @param stack Pila a consulatar.
 * @return void* Elemento guardado en la primera posición de la pila.
 */
void *PeekTop(const Stack *stack);

/**
 * @brief Verificar si una pila esta vacía.
 * 
 * @param stack Pila a consulatar.
 * @return int 1 si la pila esta vacía, 0 sino.
 */
int IsEmpty(const Stack *stack);

/**
 * @brief Obtener el tamaño de una pila.
 * 
 * @param stack Pila a consultar.
 * @return size_t Tamaño de la pila.
 */
size_t GetSize(const Stack *stack);

/**
 * @brief Vaciar Pila.
 * 
 * @param stack Pila a vaciar.
 */
void ClearStack(Stack *stack);

/**
 * @brief Destruir pila.
 * 
 * @param stack Pila a destruir.
 */
void DestroyStack(Stack *stack);

#endif