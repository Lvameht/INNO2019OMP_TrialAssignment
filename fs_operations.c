//
// Created by mavl on 16.04.19.
//
#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CONVERTER_H
#define CONVERTER_H

#include "converter.h"

#endif

#ifndef FS_OPERATIONS_H
#define FS_OPERATIONS_H

#include "fs_operations.h"

#endif


int load_image(image *image, const char *filename) {
    image->width = 0;
    image->height = 0;
    image->color_range = 0;

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: failed to open file");
        return 1;
    }

    char ppm_format[2];
    int c;

    // Parse header
    c = getc(file);
    if (c != 'P') {
        printf("Error: failed to parse PPM");
        return 1;
    }

    c = getc(file);

    if (c == '3') {
        image->format = P3;
        printf("Error: Unsupported format (P3)");
        return 3;
    } else if (c == '6') {
        image->format = P6;
    } else {
        printf("Error: Unsupported format");
        return 1;
    }

    // Read dimensions
    char found = 0;
    char buff[8] = {0};
    int buff_ptr = 0;

    char **end = malloc(sizeof(char));
    while (1) {
        c = getc(file);
        if (c == ' ' || c == '\n') {
            if (found) {
                if (image->width == 0) {
                    image->width = (unsigned int) strtol(buff, end, 10);
                } else if (image->height == 0) {
                    image->height = (unsigned int) strtol(buff, end, 10);
                } else if (image->color_range == 0) {
                    image->color_range = (unsigned char) strtol(buff, end, 10);
                    break;
                }
                memset(buff, 0, 8);
                buff_ptr = 0;
            }
        } else {
            found = 1;
            buff[buff_ptr] = (char) c;
            buff_ptr++;
        }
    }
    free(end);
    long matrix_size = image->height * image->width * 3;
    image->matrix = malloc(sizeof(char) * matrix_size);

    // Read pixel data
    for (int i = 0; i < matrix_size; i++) {
        c = getc(file);
        if (c == ' ' || c == '\n') {
            continue;
        } else {
            image->matrix[i] = (unsigned char) c;
        }
    }

    printf("Image loaded\n");
    return 0;
}

int write_image(image *image, const char *filename) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        fprintf(stderr, "I/O error\n");
        return 2;
    }
    switch (image->format) {
//        case P3:
//            break;
        case P6:
            fprintf(file, "P%d\n%d %d\n%d\n", image->format, image->width, image->height, image->color_range);
            for (int i = 0; i < image->width * image->height * 3; i++) {
                fprintf(file, "%c", image->matrix[i]);
            }
            break;
        default:
            printf("Unsupported format\n");
            return 1;
    }

    fclose(file);
    return 0;
}
