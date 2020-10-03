#include "stego.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

char encode_symbol(char symbol) {
    if (symbol == ' ')
        return 26;
    if (symbol == '.')
        return 27;
    if (symbol == ',')
        return 28;
    return symbol - 'A';
}

char decode_symbol(char code) {
    if (code == 26)
        return ' ';
    if (code == 27)
        return '.';
    if (code == 28)
        return ',';
    return 'A' + code;
}

void encode_smallest_bits(BMPImage *image, int pos, char symbol) {
    unsigned char tmp = image->data[pos];
    tmp = tmp - tmp % 32 + encode_symbol(symbol);
    image->data[pos] = tmp;
}


char decode_smallest_bits(BMPImage *image, int pos) {
    return decode_symbol(image->data[pos] % 32);
}

BMPImage *insert_text(BMPImage *input_image, const char *text_file_name, const char *key_file_name) {
    assert(input_image != NULL);
    assert(key_file_name != NULL);
    FILE *key_file = fopen(key_file_name, "r");
    assert(key_file != NULL);
    assert(text_file_name != NULL);
    FILE *text_file = fopen(text_file_name, "r");
    assert(text_file != NULL);
    BMPImage *new_image = setup_new_BMP(input_image, input_image->header.biWidth, input_image->header.biHeight);
    memcpy(new_image->data, input_image->data, sizeof(*input_image->data) * input_image->header.biSizeImage);
    char symbol = 0, color = 0;
    int x = 0, y = 0;
    fscanf(key_file, "%d %d %c", &x, &y, &color);
    while ((symbol = fgetc(text_file)) != '\n' && !feof(key_file)) {
        assert(x >= 0 && x < new_image->header.biWidth);
        assert(y >= 0 && y < new_image->header.biHeight);
        assert(color == 'B' || color == 'G' || color == 'R');
        int pos_y = (input_image->header.biHeight - y - 1) * get_image_rows_size(&input_image->header);
        int pos_x = x * BYTES_PER_PIXEL;
        if (color == 'B') {
            encode_smallest_bits(new_image, pos_x + pos_y, symbol);
        }
        if (color == 'G') {
            encode_smallest_bits(new_image, pos_x + pos_y + 1, symbol);
        }
        if (color == 'R') {
            encode_smallest_bits(new_image, pos_x + pos_y + 2, symbol);
        }
        fscanf(key_file, "%d %d %c", &x, &y, &color);
    }
    fclose(key_file);
    fclose(text_file);
    return new_image;
}

void decode_text(BMPImage *input_image, const char *output_file_name, const char *key_file_name) {
    assert(input_image != NULL);
    assert(key_file_name != NULL);
    FILE *key_file = fopen(key_file_name, "r");
    assert(key_file != NULL);
    assert(output_file_name != NULL);
    FILE *text_file = fopen(output_file_name, "w");
    assert(text_file != NULL);
    char color = 0, result_char = 0;
    int x = 0, y = 0;
    fscanf(key_file, "%d %d %c", &x, &y, &color);
    while (!feof(key_file)) {
        assert(x >= 0 && x < input_image->header.biWidth);
        assert(y >= 0 && y < input_image->header.biHeight);
        assert(color == 'B' || color == 'G' || color == 'R');
        int pos_y = (input_image->header.biHeight - y - 1) * get_image_rows_size(&input_image->header);
        int pos_x = x * BYTES_PER_PIXEL;
        if (color == 'B') {
            result_char = decode_smallest_bits(input_image, pos_x + pos_y);
        }
        if (color == 'G') {
            result_char = decode_smallest_bits(input_image, pos_x + pos_y + 1);
        }
        if (color == 'R') {
            result_char = decode_smallest_bits(input_image, pos_x + pos_y + 2);
        }
        fwrite(&result_char, sizeof(char), 1, text_file);
        fscanf(key_file, "%d %d %c", &x, &y, &color);
    }
    fclose(key_file);
    fclose(text_file);
}

