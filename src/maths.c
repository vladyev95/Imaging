#include <stdlib.h>
#include <stdio.h>
#include "my_error.h"
#include "img.h"
#include "fimg.h"
#include "maths.h"

/*
 * convolves img with kernel and returns a new image representing
 * the result
 * kernel size needs to be odd number
 */
void correlate_img(struct img *dest, const struct img *img, int *kern,
			int k_rows, int k_cols, float coeff)
{
	/* 
	 * i and j iterate through image
	 * k_i and k_j iterate through kernel
	 * acc is accumulator for current pixel
	 * ii and jj for the cur index in img w.r.t. kern
	 */
	int i, j, k_i, k_j, acc, ii, jj;
	/*
	 * must start with offset since edge pixels have no neighbours
	 * on some sides
	 * e.g.: kernel row size of 3 makes us start at pixel row 1
	 * 5 makes us start at 2, 7 at 3... etc
	 */
	for (i=k_rows/2; i<img->rows-k_rows/2; i++) {
		for (j=k_cols/2; j<img->cols-k_cols/2; j++) {
			acc = 0;
			for (k_i=0; k_i<k_rows; k_i++) {
				for (k_j=0; k_j<k_cols; k_j++) {
					ii = i-k_rows/2+k_i;
					ji = j-k_cols/2+k_j;

					acc += img->vals[ii][jj] * 
					kern[k_i * k_rows + k_j];
				}
			}
			acc = (int) (coeff * acc);
			dest->vals[i][j] = acc;
		}
	}
}

void correlate_fimg(struct fimg *dest, const struct fimg *fimg, int *kernel,
			int k_rows, int k_cols, float coeff)
{
	/* 
	 * i and j iterate through image
	 * k_i and k_j iterate through kernel
	 * acc is accumulator for current pixel
	 * ii and jj for the cur index in img w.r.t. kern
	 */
	int i, j, k_i, k_j, acc, ii, jj;
	/*
	 * must start with offset since edge pixels have no neighbours
	 * on some sides
	 * e.g.: kernel row size of 3 makes us start at pixel row 1
	 * 5 makes us start at 2, 7 at 3... etc
	 */
	for (i=k_rows/2; i<fimg->rows-k_rows/2; i++) {
		for (j=k_cols/2; j<fimg->cols-k_cols/2; j++) {
			acc = 0;
			for (k_i=0; k_i<k_rows; k_i++) {
				for (k_j=0; k_j<k_cols; k_j++) {
					ii = i-k_rows/2+k_i;
					jj = j-k_cols/2+k_j;

					acc += fimg->vals[ii][jj]
					* kernel[k_i * k_rows + k_j];
					
				}
			}
			acc = coeff * acc;
			dest->vals[i][j] = acc;
		}
	}
}
