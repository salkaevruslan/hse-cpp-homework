#ifndef POINT_LIST_H_
#define POINT_LIST_H_

#include "clist.h"
#include <stdint.h>

typedef struct point_node {
    int32_t x;
    int32_t y;
    intrusive_node node;
} point_node;

point_node *get_point(intrusive_node *node);

void remove_point(intrusive_list *list, int32_t x, int32_t y);

void add_point(intrusive_list *list, int32_t x, int32_t y);

void show_all_points(intrusive_list *list);

void remove_all_points(intrusive_list *list);

void free_list(intrusive_list *list);

#endif
