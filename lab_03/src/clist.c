#include "clist.h"
#include <stddef.h>

void init_list(struct intrusive_node *list_head) {
    list_head->next = NULL;
    list_head->prev = NULL;
}

void add_node(struct intrusive_node *list_head, struct intrusive_node *new_node) {
    new_node->prev = list_head;
    new_node->next = list_head->next;
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
    list_head->next = new_node;
}

void remove_node(struct intrusive_node *del_node) {
    if (del_node->next != NULL) {
        del_node->next->prev = del_node->prev;
        del_node->prev->next = del_node->next;
    } else {
        del_node->prev->next = NULL;
    }
}

int get_length(struct intrusive_node *list_head) {
    int result = 0;
    struct intrusive_node *ptr = list_head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
        result++;
    }
    return result;
}

