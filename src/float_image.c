#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image.h"
#include "my_error.h"

/*
 * dynamically allocates an image with given arguments
 */
struct float_image *new_float_image(uint16_t rows, uint16_t cols, uint16_t maxval)
{
	int i;
	struct float_image *img;
	
	if (!(img = malloc(sizeof(*img))))
		SYSCALL_ERROR("malloc()");
		
	img->rows = rows;
	img->cols = cols;
	img->maxval = maxval;
	if (!(img->values = malloc(sizeof(img->values[0]) * rows)))
		SYSCALL_ERROR("malloc()");
		
	for (i=0;i<img->rows;i++) {
		if (!(img->values[i] = malloc(sizeof(img->values[i][0])
			* img->cols))) {
			
			SYSCALL_ERROR("malloc()");
		}
		
		memset(img->values[i], 0, 
			sizeof(img->values[i][0]) * img->cols);
	}
	return img;
}

/*
 * returns an identicaly copy of img
 */
struct float_image *copy_float_image(const struct float_image *img)
{
	int i;
	struct float_image *new_img;
	new_img = new_float_image(img->rows, img->cols, img->maxval);
	for (i=0;i<img->rows;i++) {
		memcpy(new_img->values[i], img->values[i],
			img->cols * sizeof(img->values[i][0]));
	}
	return new_img;
}

struct float_image *convert_to_float(const struct image *img)
{
	int i, j;
	struct float_image *res;
	
	res = new_float_image(img->rows, img->cols, img->maxval);
	for (i = 0; i < res->rows; i++){
		for (j =0; j < res->cols; j++){
			res->values[i][j] = (1.0f) * img->values[i][j];
		}
	}

	return res;
}

void print_float_image(const struct float_image *img)
{
	int i, j;
	for (i=0;i<img->rows;i++) {
		for (j=0;j<img->cols;j++)
			printf("%f ", img->values[i][j]);
		putchar('\n');
	}
}

void free_float_image(struct float_image *img)
{
	int i;
	for (i=0;i<img->rows;i++)
		free(img->values[i]);
	free(img->values);
	free(img);
}
