#ifndef LIST_H
#define LIST_H

#include<stddef.h>

typedef struct NodeList Node;
typedef struct List List;

/**
 * @brief Crea una nueva lista vacía
 * @return List*: puntero a la lista creada, o NULL si falla malloc
 */
List *NewList(void);

/**
 * @brief Copia la lista que pas por parametro
 * 
 * @param list: lista a copiar
 * @return List*: puntero a la copia de la lista ingresada por parametro, o NULL si list es igual a NULL
 */
List *CopyList(const List *list);

/**
 * @brief Concatena 2 listas
 * 
 * @param list1 primera mitad de la nueva lista.
 * @param list2 segunda mitad de la nueva listz.
 * @return List*: puntero a la nueva lista conformada por las 2 listas pasadas por parametro.
 * En caso de que alguna sea nula simplemente se ignora, si ambas lo son regresa NULL
 */
List *ConcatList(const List *list1, const List *list2);

/**
 * @brief Busca todos los nodos cuyos elemetos coinciden con el elemento que se busca.
 * 
 * @param list lista donde se va a buscar
 * @param ele el elemento que se busca
 * @return List* puntero a la nueva lista formada por los nodos que sus elementos coinciden con el buscado.
 */
List *SearchElement(const List *list, void *ele);

/**
 * @brief Obtener el nodo cabeza (primero).
 * 
 * @param list lista la cual se consulta.
 * @return const Node*: puntero al nodo cabeza.
 */
const Node *GetHead(const List *list);

/**
 * @brief Obtener el nodo cola (último).
 * 
 * @param list lista la cual se ocnsulta.
 * @return const Node*: puntero al nodo cola.
 */
const Node *GetTail(const List *list);

/**
 * @brief Obtener el nodo anterior.
 * 
 * @param node nodo el cual se consulta.
 * @return const Node* puntero al nodo anterior
 */
const Node *GetPrev(const Node *node);

/**
 * @brief Ontener el siguiente nodo,
 * 
 * @param node nodo el cual se consulta.
 * @return const Node* puntero al nodo siguiente
 */
const Node *GetNext(const Node *node);

/**
 * @brief Obtener el tamaño de la lista.
 * 
 * @param list lista la cual se le consulta.
 * @return size_t tamaño de la lista pasada por parametro.
 */
size_t GetSize(const List *list);

/**
 * @brief Obtener el elemento del nodo.
 * 
 * @param node nodo el cual se consulta.
 * @return void* Elemento que guarda el nodo al que se le consulta.
 */
void *GetElement(const Node *node);

/**
 * @brief Verifica si una lista esta vacia
 * 
 * @param list 
 * @return int 1 en caso de que la lista este vacia, 0 sino.
 */
int IsEmpty(const List *list);

/**
 * @brief Agrega un nodo a una lista.
 * 
 * @param list lista donde se va agregar el nodo.
 * @param ele elemento que va a llevar el nodo
 * @param pos posición donde se va a insertar
 */
void Add(List *list, void *ele, size_t pos);

/**
 * @brief Elimina un nodo de la lista junto con su elemento.
 * 
 * @param list lista de la cual se va a eliminar el nodo
 * @param pos posición en donde se encuentra el nodo a eliminar.
 */
void Delete(List *list, size_t pos);

/**
 * @brief Buscar el elemento en un aposición espesifica.
 * 
 * @param list lista la cual se consulta.
 * @param pos posición donde se busca.
 * @return void* Elemento encontrado en el nodo en esa posición.
 */
void *SearchPosition(const List *list, size_t pos);

/**
 * @brief Divide una lista en 2.
 * 
 * @param list lista a dividir.
 * @param list1 primera mitad de la lista original.
 * @param list2 segunda mitad de la lista original.
 */
void SplitList(List *list, List **list1, List **list2);

/**
 * @brief Ordenar una lista.
 * 
 * @param list lista a ordenar.
 * @param cmp función con la cual se va a comparar los elementos de la lista.
 */
void MergeSortList(List *list, int (*cmp)(const void *, const void *));

/**
 * @brief Vaciar una lista.
 * 
 * @param list lista la cual va a ser vaciada.
 */
void ClearList(List *list);

/**
 * @brief Destruir una lista.
 * 
 * @param list lista la cual va a ser destuida.
 */
void DestroyList(List *list);

#endif