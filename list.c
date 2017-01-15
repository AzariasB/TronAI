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

void *list_node_destroy(list_node* node) {
    void *data = node->data;
    free(node);
    return data;
}


//List-related functions

list * list_create() {
    list *l = malloc(sizeof (list));
    l->size = 0;
    l->head = NULL;

    return l;
}

list *list_copy(const list *to_copy) {
    list *copy = list_create();

    for (int i = 0; i < to_copy->size; i++) {
        list_add(copy, i, list_get(to_copy, i));
    }
    return copy;
}

void **list_destroy(list *l) {
    void **data = list_clean(l);
    free(l);
    return data;
}

list_node *list_get_node(const list* a, int index) {
    if (index < 0 || index >= a->size) {
        return NULL;
    } else {
        list_node* current_node = a->head;
        for (int i = 0; i < index; i++) {
            current_node = current_node->next;
        }
        return current_node;
    }
}

void *list_get(const list*a, int index) {
    list_node *node = list_get_node(a, index);
    return node ? node->data : NULL;
}

list_node *list_add(list* target, int index, void* data) {
    if (index < 0 || index > target->size) {
        fprintf(stderr, "Tried to add node at impossible position\n");
        index = index > 0 ? index > target->size ? target->size - 1 : index : 0;
    }
    list_node *node = list_node_create(data);
    if (target->head == NULL) {
        target->head = node;
    } else if (index == 0) {
        node->next = target->head;
        target->head = node;
    } else {
        list_node *before = list_get_node(target, index - 1);
        list_node *after = before->next;
        before->next = node;
        if (after) {
            node->next = after;
        }
    }
    target->size++;

    return node;
}

void *list_remove_node(list* target, int index) {
    index = index > 0 ? index > target->size ? target->size - 1 : index : 0;
    void *data = NULL;
    if (index == 0) {
        list_node *to_rm = target->head;
        target->head = target->head->next;
        data = list_node_destroy(to_rm);
    } else {
        list_node *before_remove = list_get_node(target, index - 1);
        if (before_remove != NULL) {
            list_node *to_rm = before_remove->next;
            if (index < target->size - 1) {
                list_node *after_remove = to_rm->next;
                before_remove->next = after_remove;
            } else {
                before_remove->next = NULL;
            }
            data = list_node_destroy(to_rm);
        }
    }
    target->size--;
    return data;
}

void **list_clean(list* target) {
    void **void_arry = malloc(sizeof (*void_arry) * target->size);
    int size = target->size;
    for (int i = 0; i < size; i++) {
        void_arry[i] = list_remove_node(target, 0);
    }
    return void_arry;
}

bool list_is_empty(const list* target) {
    return target->size == 0;
}


#endif
