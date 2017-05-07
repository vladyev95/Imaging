#ifndef FIMG_H
#define FIMG_H

#include <stdint.h>

struct img;

struct fimg {
	float **vals;
	int rows, cols, max;
};


void init_fimg(struct fimg *fimg, int rows, int cols, int max);

/*
 * returns an identicaly copy of img
 */
void cp_fimg(struct fimg *dest, const struct fimg *src);


struct fimg *malloc_fimg(void);

/*
 * prints individual fimg pixel values out to stdin
 */
void print_fimg(const struct fimg *img);

/*
 * frees resources behind img
 */
void free_fimg(struct fimg *fimg);

void fimg2img(struct img *dest, const struct fimg *src);

#endif
