#ifndef STEGO_H
#define STEGO_H

#include "bmp.h"

BMPImage *insert_text(BMPImage *input_image, const char *text_file_name, const char *key_file_name);

void decode_text(BMPImage *input_image, const char *output_file_name, const char *key_file_name);

#endif

