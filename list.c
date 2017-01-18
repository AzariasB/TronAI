#include "list.h"
#ifdef CS_LIST



//List-node related functions

list_node *list_node_create(void* data) {
    list_node *node = malloc(sizeof (list_node));
    node->next = NULL;
    node->data = data;
    return node;
}

list_node *list_node_copy(list_node* to_copy) {
    list_node *copy = list_node_create(to_copy->data);
    if (to_copy->next && to_copy->next != NULL) {
        copy->next = list_node_copy(to_copy->next);
    }
    return copy;
}

void list_node_destroy(list_node* node, void (*destroy)(void *)) {
    if (node->data != NULL) {
        (*destroy)(node->data);
    }
    node->next = NULL;
    free(node);
}


//List-related functions

list * list_create() {
    list *l = malloc(sizeof (list));
    l->head_sentinel = list_node_create(NULL);
    l->tail_sentinel = list_node_create(NULL);
    l->head_sentinel->next = l->tail_sentinel;
    l->tail_sentinel->next = l->tail_sentinel;
    l->size = 0;
    return l;
}

list *list_copy(const list *to_copy) {
    list *copy = list_create();
    for (int i = 0; i < to_copy->size; i++) {
        list_add(copy, i, list_get(to_copy, i));
    }
    return copy;
}

void list_destroy(list *l, void (*destroy)(void *)) {
    list_clear(l, destroy);
    l->head_sentinel->next = NULL;
    list_node_destroy(l->head_sentinel, destroy);
    l->tail_sentinel->next = NULL;
    list_node_destroy(l->tail_sentinel, destroy);
    //    free(l);
}

list_node *list_get_node(const list* a, int index) {
    if (index < 0) {
        return a->head_sentinel;
    } else if (index >= a->size) {
        return a->tail_sentinel;
    }
    list_node *n = a->head_sentinel->next;
    while (index > 0) {
        n = n->next;
        index--;
    }
    return n;
}

void *list_get(const list*a, int index) {
    list_node *node = list_get_node(a, index);
    return node->data;
}

list_node *list_add(list* target, int index, void* data) {
    index = index > 0 ? index > target->size ? target->size : index : 0;
    list_node *before = list_get_node(target, index - 1);
    list_node *nw_node = list_node_create(data);
    nw_node->next = before->next;
    before->next = nw_node;
    target->size++;
    return nw_node;
}

void list_remove_node(list* target, int index, void (*destroy)(void *)) {
    index = index > 0 ? index > target->size ? target->size - 1 : index : 0;
    list_node *before = list_get_node(target, index - 1);
    list_node *to_delete = before->next;
    before->next = to_delete->next;
    list_node_destroy(to_delete, destroy);
    target->size--;
}

void list_clear(list* target, void (*destroy)(void*)) {
    list_node *current = target->head_sentinel->next;
    while (current != target->tail_sentinel) {
        list_node *next = current->next;
        list_node_destroy(current, destroy);
        current = next;
    }
    target->head_sentinel->next = target->tail_sentinel;
    target->size = 0;
}

bool list_is_empty(const list* target) {
    return target->size == 0;
}


#endif