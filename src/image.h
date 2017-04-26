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

/*
* Adds two images and returns the result. Values >= 255 are set to 255.
*/
struct image *add_image(const struct image *img1, const struct image *img2);

void print_image(const struct image *img);


/*
* Multiplies an image by a scalar and returns the result.
*/
struct image *scalar_mult(const struct image *img, const float scalar);
#endif
