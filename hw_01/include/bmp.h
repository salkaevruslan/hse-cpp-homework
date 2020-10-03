#ifndef BMP_H
#define BMP_H

#include <stdlib.h>
#include <inttypes.h>

#define BMP_HEADER_SIZE 54
#define BYTES_PER_PIXEL 3

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

#pragma pack(push, 1)

typedef struct {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportantL;
} BMPHeader;
#pragma pack(pop)

typedef struct {
    BMPHeader header;
    BYTE *data;
} BMPImage;

BMPImage *load_bmp(const char *file_name);

BMPImage *crop_image(BMPImage *input_image, int x, int y, int width, int height);

BMPImage *rotate_image(BMPImage *input_image);

void save_bmp(char *file_name, BMPImage *image);

void free_bmp(BMPImage *image);

int get_image_rows_size(BMPHeader *header);

BMPImage *setup_new_BMP(BMPImage *input_image, int width, int height);

#endif
