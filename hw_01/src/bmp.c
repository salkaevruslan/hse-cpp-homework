#include "bmp.h"
#include <assert.h>
#include <stdio.h>

int get_padded_bytes(BMPHeader *header) {
    return (4 - (header->biWidth * BYTES_PER_PIXEL) % 4) % 4;
}

int get_image_rows_size(BMPHeader *header) {
    return header->biWidth * BYTES_PER_PIXEL + get_padded_bytes(header);
}

int get_image_byte_size(BMPHeader *header) {
    return get_image_rows_size(header) * header->biHeight;
}

BMPImage *setup_new_BMP(BMPImage *input_image, int width, int height) {
    BMPImage *new_image = malloc(sizeof(*new_image));
    assert(new_image != NULL);
    new_image->header = input_image->header;
    new_image->header.biHeight = height;
    new_image->header.biWidth = width;
    new_image->header.biSizeImage = get_image_byte_size(&new_image->header);
    new_image->header.bfSize = BMP_HEADER_SIZE + new_image->header.biSizeImage;
    new_image->data = malloc(sizeof(*new_image->data) * new_image->header.biSizeImage);
    assert(new_image->data != NULL);
    return new_image;
}

BMPImage *load_bmp(const char *file_name) {
    assert(file_name != NULL);
    FILE *input_file = fopen(file_name, "rb");
    assert(input_file != NULL);
    BMPImage *image = malloc(sizeof(*image));
    assert(image != NULL);
    fread(&image->header, BMP_HEADER_SIZE, 1, input_file);
    assert(&image->header != NULL);
    image->data = malloc(sizeof(*image->data) * image->header.biSizeImage);
    assert(image->data != NULL);
    fread(image->data, image->header.biSizeImage, 1, input_file);
    fclose(input_file);
    return image;
}

BMPImage *crop_image(BMPImage *input_image, int x, int y, int width, int height) {
    assert(input_image != NULL);
    assert(0 < width && width <= input_image->header.biWidth);
    assert(0 < height && height <= input_image->header.biHeight);
    assert(width + x <= input_image->header.biWidth);
    assert(height + y <= input_image->header.biHeight);
    BMPImage *new_image = setup_new_BMP(input_image, width, height);
    int index = 0;
    int pos_y = (input_image->header.biHeight - y - height) * get_image_rows_size(&input_image->header);
    int pos_x = x * BYTES_PER_PIXEL;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < BYTES_PER_PIXEL; k++) {
                new_image->data[index] = input_image->data[pos_y + pos_x];
                index++;
                pos_x++;
            }
        }
        int padding = get_padded_bytes(&new_image->header);
        for (int j = 0; j < padding; j++) {
            new_image->data[index] = 0x00;
            index++;
        }
        pos_y += get_image_rows_size(&input_image->header);
        pos_x = x * BYTES_PER_PIXEL;
    }
    return new_image;
}

BMPImage *rotate_image(BMPImage *input_image) {
    assert(input_image != NULL);
    BMPImage *new_image = setup_new_BMP(input_image, input_image->header.biHeight, input_image->header.biWidth);
    int index = 0;
    for (int pos_x = (input_image->header.biWidth - 1) * BYTES_PER_PIXEL; pos_x >= 0; pos_x -= BYTES_PER_PIXEL) {
        for (int pos_y = 0; pos_y < input_image->header.biHeight; pos_y++) {
            for (int k = 0; k < BYTES_PER_PIXEL; k++) {
                new_image->data[index] = input_image->data[pos_y * get_image_rows_size(&input_image->header)
                                                           + pos_x + k];
                index++;
            }
        }
        int padding = get_padded_bytes(&new_image->header);
        for (int j = 0; j < padding; j++) {
            new_image->data[index] = 0x00;
            index++;
        }
    }
    return new_image;
}


void save_bmp(char *file_name, BMPImage *image) {
    FILE *file = fopen(file_name, "wb");
    fwrite(&image->header, BMP_HEADER_SIZE, 1, file);
    fwrite(image->data, image->header.biSizeImage, 1, file);
    fclose(file);
}

void free_bmp(BMPImage *image) {
    free(image->data);
    free(image);
}

