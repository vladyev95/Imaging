#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>


struct image {
	uint8_t **values;
	uint16_t rows, cols, maxval;
};

struct image *read_image(const char *path);

/*
 * writes img to path as a .pgm image
 */
void write_image(const struct image *img, const char *path);

/*
 * reads the .pgm image and returns a structure representing it
 * returned image should be used with free_image() to deallocate
 */
 
 /*
 * frees the image
 */
void free_image(struct image *img);

/*
 * dynamically allocates an image with given arguments
 */
struct image *new_image(uint16_t rows, uint16_t cols, uint16_t maxval);

/*
 * returns an identicaly copy of img
 */
struct image *copy_image(const struct image *img);


#endif
