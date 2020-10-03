#include "bmp.h"
#include "stego.h"
#include <assert.h>
#include <string.h>

void crop_rotate(char **argv) {
    BMPImage *image = load_bmp(argv[2]);
    BMPImage *cropped_image = crop_image(image, atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
    BMPImage *new_image = rotate_image(cropped_image);
    save_bmp(argv[3], new_image);
    free_bmp(image);
    free_bmp(cropped_image);
    free_bmp(new_image);
}

void insert_message(char **argv) {
    BMPImage *image = load_bmp(argv[2]);
    BMPImage *new_image = insert_text(image, argv[5], argv[4]);
    save_bmp(argv[3], new_image);
    free_bmp(image);
    free_bmp(new_image);
}

void extract_message(char **argv) {
    BMPImage *image = load_bmp(argv[2]);
    decode_text(image, argv[4], argv[3]);
    free_bmp(image);
}

int main(int argc, char *argv[]) {
    assert(argc == 8 || argc == 6 || argc == 5);
    if (!strcmp(argv[1], "crop-rotate") && argc == 8) {
        crop_rotate(argv);
    }
    if (!strcmp(argv[1], "insert") && argc == 6) {
        insert_message(argv);
    }
    if (!strcmp(argv[1], "extract") && argc == 5) {
        extract_message(argv);
    }
    return 0;
}
