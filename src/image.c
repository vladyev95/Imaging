#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image.h"
#include "my_error.h"

/*
 * writes img to path as a .pgm image
 */
void write_image(const struct image *img, const char *path)
{
	int i, j;
	FILE *fp;
	if (!(fp = fopen(path, "w")))
		SYSCALL_ERROR("fopen()");
		
	/*
	 * header consists of "nrows ncols" on 1st line
	 * and "pixelmaxval\n" on 2nd line, followed by all pixel values
	 * the P5 is format of the bitmap image, we use specifically P5
	 */
	fprintf(fp, "P5\n%hu %hu\n%hu\n", img->cols, img->rows, img->maxval);
	for (i=0;i<img->rows;i++)
		for (j=0;j<img->cols;j++)
			fprintf(fp, "%c", img->values[i][j]);
			
	if (fflush(fp))
		SYSCALL_ERROR("fflush()");
		
	if (fclose(fp))
		SYSCALL_ERROR("fclose()");
}

/*
 * reads the .pgm image and returns a structure representing it
 * returned image should be used with free_image() to deallocate
 */
struct image *read_image(const char *path)
{
	int i, j;
	uint16_t rows, cols, maxval;
	FILE *fp;
	struct image *img;
	
	if (!(fp = fopen(path, "r")))
		SYSCALL_ERROR("fopen()");
			
	if (fscanf(fp, "P5\n%hu %hu\n%hu\n", &cols, &rows, &maxval) != 3)
		ERROR("unable to read image header");

	img = new_image(rows, cols, maxval);
	for (i=0;i<img->rows;i++) {
		for (j=0;j<img->cols;j++) {
			if (fscanf(fp, "%c", &img->values[i][j]) != 1) {
				ERROR("unable to read pixels");
			}
		}
	}

	if (fclose(fp))
		SYSCALL_ERROR("fclose()");
		
	return img;
}

/*
 * frees the image
 */
void free_image(struct image *img)
{
	int i;
	for (i=0;i<img->rows;i++)
		free(img->values[i]);
	free(img->values);
	free(img);
}

/*
 * dynamically allocates an image with given arguments
 */
struct image *new_image(uint16_t rows, uint16_t cols, uint16_t maxval)
{
	int i;
	struct image *img;
	
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
struct image *copy_image(const struct image *img)
{
	int i;
	struct image *new_img;
	new_img = new_image(img->rows, img->cols, img->maxval);
	for (i=0;i<img->rows;i++) {
		memcpy(new_img->values[i], img->values[i],
			img->cols * sizeof(img->values[i][0]));
	}
	return new_img;
}

struct image *add_image(const struct image *img1, const struct image *img2)
{
	int row, col, sum;
	//Should check for same image dimensions and throw error if not equal.
	struct image *added_image = new_image(img1->rows, img1->cols, img1->maxval);

	for (row = 0; row < added_image->rows; row++){
		for (col = 0; col < added_image->cols; col++){
			sum = (img1->values[row][col] + img2->values[row][col]);
			if (sum >= added_image->maxval)
				added_image->values[row][col] = added_image->maxval;
			else
				added_image->values[row][col] = sum;
		}
	}

	//Needs to be freed later.
	return added_image;
}

/*
* Multiplies an image by a scalar and returns the result. Fractions will
* be truncated.
*/
struct image *scalar_mult(const struct image *img, const float scalar)
{
	int row, col;
	struct image *result = new_image(img->rows, img->cols, img->maxval);
	
	for (row = 0; row < result->rows; row++){
		for (col = 0; col < result->cols; col++){
			result->values[row][col] = img->values[row][col] * scalar;
		}
	}

	//Will need to be freed.
	return result;
}
