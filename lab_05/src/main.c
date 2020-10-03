#include "point_list.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define BYTE_MAX_VALUE 256
#define BYTES_PER_ELEM 3

const int32_t MAX_VALUE = 256 * 256 * 256;

int32_t bin_to_dec(unsigned char *buffer) {
    int32_t x = 0;
    int32_t k = 1;
    for (int i = 0; i < BYTES_PER_ELEM; ++i) {
        x += k * buffer[i];
        k *= BYTE_MAX_VALUE;
    }
    if (buffer[BYTES_PER_ELEM - 1] >= BYTE_MAX_VALUE / 2) {
        x -= MAX_VALUE;
    }
    return x;
}

int32_t convert(int32_t value) {
    if (value < 0)
        value += MAX_VALUE;
    return value;
}

void printbin(FILE *output_file, int32_t value) {
    value = convert(value);
    unsigned char buffer[BYTES_PER_ELEM];
    for (int i = 0; i < BYTES_PER_ELEM; i++) {
        buffer[i] = value % BYTE_MAX_VALUE;
        value /= BYTE_MAX_VALUE;
    }
    fwrite(buffer, sizeof(char), BYTES_PER_ELEM, output_file);
}

void count(struct intrusive_node *node, void *data) {
    (void) node;
    (*((int *) data))++;
}

void print(struct intrusive_node *node, void *format) {
    point_node *pnode = get_point(node);
    printf((char *) format, pnode->x, pnode->y);
}

void savetext(struct intrusive_node *node, void *data) {
    FILE *fout = (FILE *) data;
    point_node *pnode = get_point(node);
    fprintf(fout, "%d %d\n", pnode->x, pnode->y);
}

void savebin(struct intrusive_node *node, void *data) {
    FILE *output_file = (FILE *) data;
    point_node *pnode = get_point(node);
    printbin(output_file, pnode->x);
    printbin(output_file, pnode->y);
}

void loadbin(FILE *input_file, intrusive_list *l) {
    unsigned char buffer[2 * BYTES_PER_ELEM];
    while (fread(buffer, sizeof(char), 2 * BYTES_PER_ELEM, input_file) == 2 * BYTES_PER_ELEM) {
        int32_t x = bin_to_dec(buffer);
        int32_t y = bin_to_dec(buffer + BYTES_PER_ELEM);
        add_point(l, x, y);
    }
}

void loadtext(FILE *input_file, intrusive_list *l) {
    int32_t x, y;
    while (fscanf(input_file, "%d%d", &x, &y) == 2) {
        add_point(l, x, y);
    }
}

int main(int argc, char *argv[]) {
    intrusive_list list;
    init_list(&list);
    assert(argc == 4 || argc == 5);
    if (strcmp(argv[1], "loadtext") == 0) {
        FILE *input_file = fopen(argv[2], "r");
        assert(input_file);
        loadtext(input_file, &list);
        fclose(input_file);
    }
    if (strcmp(argv[1], "loadbin") == 0) {
        FILE *input_file = fopen(argv[2], "rb");
        assert(input_file);
        loadbin(input_file, &list);
        fclose(input_file);
    }
    if (strcmp(argv[3], "print") == 0) {
        apply(&list, print, argv[4]);
        printf("\n");
    }
    if (strcmp(argv[3], "count") == 0) {
        int cnt = 0;
        int *ptr = &cnt;
        apply(&list, count, ptr);
        printf("%d\n", cnt);
    }
    if (strcmp(argv[3], "savetext") == 0) {
        FILE *output_file = fopen(argv[4], "w");
        assert(output_file);
        apply(&list, savetext, output_file);
        fclose(output_file);
    }
    if (strcmp(argv[3], "savebin") == 0) {
        FILE *output_file = fopen(argv[4], "wb");
        assert(output_file);
        apply(&list, savebin, output_file);
        fclose(output_file);
    }
    free_list(&list);
    return 0;
}
