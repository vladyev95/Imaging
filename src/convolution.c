#include <stdlib.h>
#include <stdio.h>
#include "my_error.h"
#include "image.h"
#include "convolution.h"

static int **kernel_flip(size_t k_rows, size_t k_cols, 
				int kernel[k_rows][k_cols]);

/*
 * convolves img with kernel and returns a new image representing
 * the result
 * kernel size needs to be odd number
 */
struct image *convolve(const struct image *img, size_t k_rows, size_t k_cols, 			int kernel[k_rows][k_cols], float coeff)
{
	struct image *out;
	/* 
	 * i and j iterate through image
	 * k_i and k_j iterate through kernel
	 * acc is accumulator for current pixel
	 * mask is kernel flipped vertically and horizontally
	 */
	int i, j, k_i, k_j, acc, **mask, k_r, k_c;
	
	/* required for integer arithmetic to work correctly in loop */
	k_r = (int) k_rows;
	k_c = (int) k_cols;
	
	/* by definition of convolution, kernel must be flipped */
	mask = kernel_flip(k_rows, k_cols, kernel);
	out = new_image(img->rows, img->cols, img->maxval);
	
	/*
	 * must start with offset since edge pixels have no neighbours
	 * on some sides
	 * e.g.: kernel row size of 3 makes us start at pixel row 1
	 * 5 makes us start at 2, 7 at 3... etc
	 */
	for (i=k_r/2;i<img->rows-k_r/2;i++)
		for (j=k_c/2;j<img->cols-k_c/2;j++) {
			acc = 0;
			for (k_i=-k_r/2;k_i<=k_r/2;k_i++)
				for (k_j=-k_c/2;k_j<=k_c/2;k_j++) {
					acc += 
					img->values[i+k_i][j+k_j] *
					mask[k_i+k_r/2][k_j+k_c/2];
				}
			acc = (int) (coeff * acc);
			out->values[i][j] = acc;
		}
		
		
	for (i=0;i<k_rows;i++)
		free(mask[i]);
	free(mask);

	return out;
}

struct float_image *convolve_float(const struct float_image *img, size_t k_rows, size_t k_cols, 			int kernel[k_rows][k_cols], float coeff)
{
	struct float_image *out;
	/* 
	 * i and j iterate through image
	 * k_i and k_j iterate through kernel
	 * acc is accumulator for current pixel
	 * mask is kernel flipped vertically and horizontally
	 */
	int i, j, k_i, k_j, acc, **mask, k_r, k_c;
	
	/* required for integer arithmetic to work correctly in loop */
	k_r = (int) k_rows;
	k_c = (int) k_cols;
	
	/* by definition of convolution, kernel must be flipped */
	mask = kernel_flip(k_rows, k_cols, kernel);
	out = new_float_image(img->rows, img->cols, img->maxval);
	
	/*
	 * must start with offset since edge pixels have no neighbours
	 * on some sides
	 * e.g.: kernel row size of 3 makes us start at pixel row 1
	 * 5 makes us start at 2, 7 at 3... etc
	 */
	for (i=k_r/2;i<img->rows-k_r/2;i++)
		for (j=k_c/2;j<img->cols-k_c/2;j++) {
			acc = 0;
			for (k_i=-k_r/2;k_i<=k_r/2;k_i++)
				for (k_j=-k_c/2;k_j<=k_c/2;k_j++) {
					acc += 
					img->values[i+k_i][j+k_j] *
					mask[k_i+k_r/2][k_j+k_c/2];
				}
			acc = (float) (coeff * acc);
			out->values[i][j] = acc;
		}
		
		
	for (i=0;i<k_rows;i++)
		free(mask[i]);
	free(mask);

	return out;
}



/*
 * flips the kernel across both the horizontal and vertical axes
 * returned mask is dynamically allocated, must be freed
 */
static int **kernel_flip(size_t k_rows, size_t k_cols, 
				int kernel[k_rows][k_cols])
{
	int **mask, i, j;
	if (!(mask = malloc(sizeof(mask[0]) * k_rows)))
		SYSCALL_ERROR("malloc()");
		
	for (i=0;i<k_rows;i++)
		if (!(mask[i] = malloc(sizeof(mask[i][0]) * k_cols)))
			SYSCALL_ERROR("malloc()");
			
	for (i=0;i<k_rows;i++)
		for (j=0;j<k_cols;j++)
			mask[k_rows-i-1][k_cols-j-1] = kernel[i][j];

	return mask;
}

void print_image(const struct image *img)
{
	int i, j;
	for (i=0;i<img->rows;i++) {
		for (j=0;j<img->cols;j++)
			printf("%d ", img->values[i][j]);
		putchar('\n');
	}
}
