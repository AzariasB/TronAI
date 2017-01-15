#ifndef CS_LIST
#define CS_LIST

#include <stdio.h>
#include <stdlib.h>
#define NELEMS(x)(sizeof(x) / sizeof(*x))

typedef struct list_node {
    struct list_node * next;
    void *data;
} list_node;

typedef struct list {
    struct list_node * head;
    int size;
} list;

typedef enum {
    false, true
} bool;

//List node-relatedf functions

list_node *list_node_create(void *data);

list_node *list_node_copy(list_node *to_copy);

/**
 * Destroys the list_node, without
 * destroying its data,
 * the data must be properly destroyed by
 * the original owner of it.
 * 
 * @param node
 * @return the data of the node to destroy
 */
void *list_node_destroy(list_node *node);

///


// List -related functions

list *list_create();

list *list_copy(const list *to_copy);

void **list_destroy(list *l);

list_node *list_get_node(const list *a, int index);

/**
 *  Re
 *
 * @param a
 * @param index
 * @return
 */
void *list_get(const list* a, int index);

/**
 * Insert a node in the list at the given
 * index with the given data
 * If the index is less than zero, is inserted at the index 0
 * If the index is more than the list length, is inserted at
 * the back of the list
 *
 * @param target
 * @param index
 * @param data
 * @return
 */
list_node *list_add(list *target, int index, void *data);

/**
 *Delete the node at the given index
 * and returns the data of this node
 * the returned data MUST be then deleted by
 * the pointer owner using the appropriate
 * destroy method
 *
 * @param target the target list
 * @param index the index of the element to remove
 * @return the data of the removed node
 */
void *list_remove_node(list *target, int index);

/**
 * Deletes all the nodes of the given list
 * return an array of pointer to the data
 * of each node
 *
 * @param target the list to clean
 * @return an array of pointer, pointing to the data of each node of the list
 */
void **list_clean(list *target);

//sfBool
bool list_is_empty(const list *target);

//

#endif
