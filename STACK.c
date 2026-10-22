#include<stdio.h>
#include<stdlib.h>
#include"STACK.h"

struct NodeStack{
    void *element; // Elemento guardado en el nodo
    struct NodeStack *below; // puntero al nodo de abajo
};

struct Stack{
    size_t size; // Tamaño de la pila
    Node *top; // puntero al nodo en la cúspide de la pila
};

Stack *NewStack(void){
    Stack *stack;

    stack = (Stack *)malloc(sizeof(Stack));
    if(stack != NULL){
        stack->top = NULL;
        stack->size = 0;
    }

    return stack;
}

void Push(Stack *stack, void *element){
    Node *new;

    if(stack != NULL){
        new = (Node *)malloc(sizeof(Node));
        if(new != NULL){
            new->element = element;
            if(stack->top == NULL){
                stack->top = new;
                stack->top->below = NULL;
            }else{
                new->below = stack->top;
                stack->top = new;
            }
            stack->size++;
        }
    }
}

void *Pop(Stack *stack){
    Node *aux;

    if(stack != NULL){
        if(stack->top != NULL){
            aux = stack->top;
            stack->top = stack->top->below;
            free(aux);
            stack->size--;
        }
    }
}

void *PeekTop(const Stack *stack){
    return (stack != NULL && stack->top != NULL) ? stack->top->element : NULL;
}

int IsEmpty(const Stack *stack){
    return ((stack == NULL) || (stack->top == NULL)) ? 1 : 0;
}

size_t GetSize(const Stack *stack){
    return (stack != NULL) ? stack->size : 0;
}

void ClearStack(Stack *stack){
    Node *aux;

    if(stack != NULL){
        while(stack->top != NULL){
            aux = stack->top;
            stack->top = stack->top->below;
            free(aux);
            stack->size--;
        }

        stack->size = 0;
        stack->top = NULL;
    }
}

void DestroyStack(Stack *stack){
    Node *aux;

    if(stack != NULL){
        while(stack->top != NULL){
            aux = stack->top;
            stack->top = stack->top->below;
            free(aux);
        }
        free(stack);
    }

}
