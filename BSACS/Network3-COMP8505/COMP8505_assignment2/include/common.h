#ifndef COMP8505_ASSIGNMENT2_COMMON_H
#define COMP8505_ASSIGNMENT2_COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <getopt.h>
#include <regex.h>
#include <inttypes.h>


struct options_image {
    /* carrier */
    char carrier_name[32];
    char carrier_type[16];
    unsigned int carrier_img_size;
    unsigned int carrier_pixel_num;
    unsigned int carrier_actual_size;
    uint32_t carrier_width;
    uint32_t carrier_height;
    uint16_t carrier_bpp;
    uint32_t carrier_row_size;
    uint32_t carrier_pixel_data_size;
    uint16_t carrier_padding;
    uint32_t carrier_offset;

    /* hiding */
    char hiding_name[32];
    char hiding_type[16];
    unsigned int hiding_img_size;
    unsigned int hiding_pixel_num;
    unsigned int hiding_actual_size;
    uint32_t hiding_width;
    uint32_t hiding_height;
    uint16_t hiding_bpp;
    uint32_t hiding_row_size;
    uint32_t hiding_pixel_data_size;
    uint16_t hiding_padding;


    /* result */
    char result_name[32];
    char result_type[16];
    unsigned int result_img_size;
    unsigned int result_pixel_num;
    unsigned int result_actual_size;
    uint32_t result_width;
    uint32_t result_height;
    uint16_t result_bpp;
    uint32_t result_row_size;
    uint32_t result_pixel_data_size;
    uint16_t result_padding;
    uint32_t result_offset;

    /* flag for encode/decode */
    char flag;
};

// Total: 54 bytes
typedef struct bitmap {          // Total: 54 bytes
    uint16_t  type;             // Magic identifier: 0x4d42 (0)
    uint32_t  size;             // File size in bytes (2)
    uint16_t  reserved1;        // Not used (6)
    uint16_t  reserved2;        // Not used (8)
    uint32_t  offset;           // Offset to image data in bytes from beginning of file (54 bytes) (10)
    uint32_t  dib_header_size;  // DIB Header size in bytes (40 bytes) (14)
    uint32_t  width;            // Width of the image (18)
    uint32_t  height;           // Height of image (22)
    uint16_t  num_planes;       // Number of color planes (26)
    uint16_t  bits_per_pixel;   // Bits per pixel (28)
    uint32_t  compression;      // Compression type (30)
    uint32_t  image_size_bytes; // Image size in bytes (34)
    uint32_t  x_resolution_ppm; // Pixels per meter (38)
    uint32_t  y_resolution_ppm; // Pixels per meter (42)
    uint32_t  num_colors;       // Number of colors (46)
    uint32_t  important_colors; // Important colors (50)
} BMPHeader;


#endif //COMP8505_ASSIGNMENT2_COMMON_H
