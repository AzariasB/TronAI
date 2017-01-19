#ifndef CS_LIST
#define CS_LIST

#include <stdio.h>
#include <stdlib.h>
#include <SFML/Config.h>

typedef struct list_node {
    struct list_node * next;
    void *data;
} list_node;

typedef struct list {
    list_node * head_sentinel;
    list_node *tail_sentinel;
    int size;
} list;


//List node-relatedf functions

list_node *list_node_create(void *data);

list_node *list_node_copy(list_node *to_copy, void *(*copier)(void *));

/**
 * Destroys the list_node, without
 * destroying its data,
 * the data must be properly destroyed by
 * the original owner of it.
 * 
 * @param node
 * @return the data of the node to destroy
 */
void list_node_destroy(list_node *node, void (*destroy)(void *data));

///


// List -related functions

list *list_create();

/**
 * Copies every element of the list
 * in a new list
 * 
 * @param to_copy the list to copy
 * @param copier the function to use to copy a single element 
 * @return the copied list
 */
list *list_copy(const list *to_copy, void *(*copier)(void *));

void list_destroy(list *l, void (*destroy)(void *));

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
 * Add the data at the end of the list
 * 
 * @param target the list to use
 * @param data the data to push in the list
 * @return the node created
 */
list_node *list_push(list *target, void *data);


/**
 * Remove the last element of the list
 * 
 * @param target the list to use
 * @param destroyer the function to destroy the last element
 */
void list_pop(list * target, void (*destroyer)(void*));

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
void list_remove_node(list *target, int index, void (*destroy)(void *));

/**
 * Deletes all the nodes of the given list
 * return an array of pointer to the data
 * of each node
 *
 * @param target the list to clean
 * @return an array of pointer, pointing to the data of each node of the list
 */
void list_clear(list *target, void (*destroy)(void *));


/**
 * Returns wether the list is empty
 * 
 * @param target the list to check
 * @return wether the list is empty
 */
sfBool list_is_empty(const list *target);

/**
 * Filters the list with the given predicate
 * and returns a newly created list containing only
 * the elements with a 'true' predicate
 * 
 * @param to_filter the list to filter
 * @param predicate a function that returs wether to keep the data
 * @return the filtered list
 */
list *list_filter(const list *to_filter, void *(*copier)(void *), sfBool(*predicate)(void *));


/**
 * Creates a new list and changes all the element of the 
 * list with the given function
 * 
 * @param to_map the list to map
 * @param mapper the function to transform the element of the list
 * @return a mapped list
 */
list *list_map(const list *to_map, void *(*copier)(void *), void (*mapper)(void *));

/**
 * Iterate over the elements of the list
 * and call the function for each element
 * 
 * @param to_each  the list to iterate over
 * @param func the function to call for each element of the list
 */
void list_each(const list *to_each, void (*func)(void *));

#endif
