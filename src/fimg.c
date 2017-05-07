#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "img.h"
#include "fimg.h"
#include "my_error.h"


void init_fimg(struct fimg *fimg, int rows, int cols, int max)
{
	int i;
	fimg->rows = rows;
	fimg->cols = cols;
	fimg->max = max;
	if (!(fimg->vals = malloc(sizeof(fimg->vals[0]) * rows)))
		ERROR("init_fimg() malloc()", errno);
	for (i=0; i<rows; i++)
		if (!(fimg->vals[i] = malloc(sizeof(fimg->vals[i][0]) * cols)))
			ERROR("inint_fimg() malloc()", errno);
}


/*
 * returns an identicaly copy of fimg
 */
void cp_fimg(struct fimg *dest, const struct fimg *src)
{
	int i;
	for (i=0; i<src->rows; i++) {
		memcpy(dest->vals[i], src->vals[i],
			src->cols * sizeof(src->vals[i][0]));
	}
}

struct fimg *malloc_fimg(void)
{
	struct fimg *p;
	if (!(p = malloc(sizeof(*p))))
		ERROR("malloc_fimg() malloc()", errno);
	return p;
}


void print_fimg(const struct fimg *fimg)
{
	int i, j;
	for (i=0; i<fimg->rows; i++) {
		for (j=0;j<fimg->cols;j++)
			printf("%f ", fimg->vals[i][j]);
		putchar('\n');
	}
}

void free_fimg(struct fimg *img)
{
	int i;
	for (i=0; i<img->rows; i++)
		free(img->vals[i]);
	free(img->vals);
}

void fimg2img(struct img *dest, const struct fimg *src)
{
	int i, j;
	for (i=0; i<src->rows; i++)
		for (j=0; j<src->cols; j++)
			dest->vals[i][j] = src->vals[i][j];
}
