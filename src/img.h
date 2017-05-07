#ifndef IMG_H
#define IMG_H

#include <stdint.h>

struct fimg;

struct img {
	uint8_t **vals;
	int rows, cols, max;
};


void init_img(struct img *img, int rows, int cols, int max);

void read_img(struct img *dest, const char *path);

/*
 * writes img to path as a .pgm image
 */
void write_img(const struct img *img, const char *path);
 
 /*
 * frees the image
 */
void free_img(struct img *img);

/*
 * dynamically allocates an image with given arguments
 */
struct img *malloc_img(void);

/*
 * returns an identicaly copy of img
 */
void cp_img(struct img *dest, const struct img *src);

void img2fimg(struct fimg *dest, const struct img *src);

/*
 * prints pixel values of img to stdin
 */
void print_img(const struct img *img);

/*
* frees the resources behind img
*/
void free_img(struct img *img);

#endif
