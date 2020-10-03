#ifndef CLIST_H_
#define CLIST_H_

struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
};

void init_list(struct intrusive_node *list_head);

void add_node(struct intrusive_node *list_head, struct intrusive_node *new_node);

void remove_node(struct intrusive_node *node);

int get_length(struct intrusive_node *list_head);

#endif
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))


