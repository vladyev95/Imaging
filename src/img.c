#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "img.h"
#include "fimg.h"
#include "my_error.h"


void init_img(struct img *img, int rows, int cols, int max)
{
	int i;
	img->rows = rows;
	img->cols = cols;
	img->max = max;
	if (!(img->vals = malloc(sizeof(img->vals[0]) * rows)))
		ERROR("read_img() malloc()", errno);
	for (i=0; i<rows; i++) 
		if (!(img->vals[i] = malloc(sizeof(img->vals[i][0]) * cols)))
			ERROR("init_img() malloc()", errno);
}

/*
 * reads path as .pgm image and places contents into dest
 */
void read_img(struct img *dest, const char *path)
{
	int i, j;
	FILE *fp;
	
	if (!(fp = fopen(path, "r")))
		ERROR("fopen()", errno);
			
	if (fscanf(fp, "P5\n%d %d\n%d\n", 
			&dest->cols, &dest->rows, &dest->max) != 3)
		ERROR("unable to read image header", 0);
	
	if (!(dest->vals = malloc(sizeof(dest->vals[0]) * dest->rows)))
		ERROR("read_img() malloc()", errno);
	for (i=0;i<dest->rows;i++) {
		if (!(dest->vals[i] = malloc(sizeof(dest->vals[i][0]) * 
				dest->cols))) {
			ERROR("read_img() malloc()", errno);
		}

		for (j=0;j<dest->cols;j++) {
			if (fscanf(fp, "%c", &dest->vals[i][j]) != 1) {
				ERROR("read_img() unable to read pixels", 0);
			}
		}
	}

	if (fclose(fp))
		ERROR("fclose()", errno);
}

/*
 * writes img to path as a .pgm image
 */
void write_img(const struct img *img, const char *path)
{
	int i, j;
	FILE *fp;
	if (!(fp = fopen(path, "w")))
		ERROR("fopen()", errno);
		
	/*
	 * header consists of "nrows ncols" on 1st line
	 * and "pixelmaxval\n" on 2nd line, followed by all pixel values
	 * the P5 is format of the bitmap image, we use specifically P5
	 */
	fprintf(fp, "P5\n%hu %hu\n%hu\n", img->cols, img->rows, img->max);
	for (i=0;i<img->rows;i++)
		for (j=0;j<img->cols;j++)
			fprintf(fp, "%c", img->vals[i][j]);
			
	if (fflush(fp))
		ERROR("fflush()", errno);
		
	if (fclose(fp))
		ERROR("fclose()", errno);
}


/*
 * frees the resources behind img
 */
void free_img(struct img *img)
{
	int i;
	for (i=0;i<img->rows;i++)
		free(img->vals[i]);
	free(img->vals);
}

struct img *malloc_img(void)
{
	struct img *p;
	if (!(p = malloc(sizeof(*p))))
		ERROR("malloc_img() malloc()", errno);
	return p;
}

/*
 * returns an identicaly copy of img
 */
void cp_img(struct img *dest, const struct img *src)
{
	int i;
	dest->rows = src->rows;
	dest->cols = src->cols;
	dest->max = src->max;
	for (i=0; i<src->rows; i++) {
		memcpy(dest->vals[i], src->vals[i],
			src->cols * sizeof(src->vals[i][0]));
	}
}

/*
 * copies src into dest
 */
void img2fimg(struct fimg *dest, const struct img *src)
{
	int i, j;
	for (i=0; i<src->rows; i++)
		for (j=0; j<src->cols; j++)
			dest->vals[i][j] = src->vals[i][j];
}
