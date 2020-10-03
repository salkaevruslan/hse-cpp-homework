#include"clist.h"
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include <stdbool.h>
#include <string.h>

struct point {
    int x, y;
    struct intrusive_node node;
};

void add_point(struct intrusive_node *list_head, int x, int y) {
    struct point *new_node = malloc(sizeof(struct point));
    new_node->x = x;
    new_node->y = y;
    add_node(list_head, &new_node->node);
}

void remove_point(struct intrusive_node *list_head, int x, int y) {
    struct intrusive_node *ptr = list_head;
    struct point *item;
    while (ptr->next != NULL) {
        item = container_of(ptr->next, struct point, node);
        if (item->x == x && item->y == y) {
            remove_node(ptr->next);
            free(item);
        } else
            ptr = ptr->next;
    }
}

void show_all_points(struct intrusive_node *list_head) {
    struct intrusive_node *ptr = list_head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
        struct point *item = container_of(ptr, struct point, node);
        printf("(%d %d) ", item->x, item->y);
    }
    printf("\n");
}

void remove_all_points(struct intrusive_node *list_head) {
    struct intrusive_node *ptr;
    while (list_head->next != NULL) {
        ptr = list_head->next;
        remove_node(ptr);
        free(container_of(ptr, struct point, node));
    }
}

void free_list(struct intrusive_node *list_head) {
    remove_all_points(list_head);
}

int main() {
    struct intrusive_node list_head;
    init_list(&list_head);
    char str[256];
    int x, y;
    while (true) {
        scanf("%255s", str);
        if (strcmp(str, "exit") == 0) {
            break;
        }
        if (strcmp(str, "rma") == 0) {
            remove_all_points(&list_head);
            continue;
        }
        if (strcmp(str, "len") == 0) {
            printf("%d\n", get_length(&list_head));
            continue;
        }
        if (strcmp(str, "print") == 0) {
            show_all_points(&list_head);
            continue;
        }
        if (strcmp(str, "add") == 0) {
            scanf("%i%i", &x, &y);
            add_point(&list_head, x, y);
            continue;
        }
        if (strcmp(str, "rm") == 0) {
            scanf("%d%d", &x, &y);
            remove_point(&list_head, x, y);
            continue;
        }
        printf("Unknown command\n");
    }
    free_list(&list_head);
    return 0;
}

