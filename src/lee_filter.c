#include <math.h>
#include "img.h"
#include "lee_filter.h"

/*
 * calculates the mean of the pixels of img
 * of the window of size w_size x w_size centered at pixel [i,j]
 */
static float w_mean(const struct img *img, int i, int j, int w_size);

/*
 * calculates the variance of the pixels of img
 * of the window of size w_size x w_size centered at pixel [i,j]
 */
static float w_var(const struct img *img, int i, int j, int w_size,
		float w_mean);
		
/*
 * returns the mean of all the pixels in img 
 */
static float img_mean(const struct img *img);

/*
 * returns the variance of all the pixels in img 
 */
static float img_var(const struct img *img, float img_mean);


/*
 * applies the Lee image filter to the img
 * returns a new image that is the filtered version
 * w_size is the size of the kernel window to use
 * w_size must be odd, or unexpected behavior may occur
 */
void lee_filter(struct img *dest, const struct img *img, int w_size)
{
 	/* i j iterate img , w_s is w_size as int for loop logic to work */
	int i, j;
	/* w_m=w_mean w_v=w_var img_m=img_mean img_v=img_var */
	float w_m, w_v, img_m, img_v, weight;
	img_m = img_mean(img);
	img_v = img_var(img, img_m);
	for (i=w_size/2; i<img->rows-w_size/2; i++)
		for (j=w_size/2; j<img->cols-w_size/2; j++) {
			w_m = w_mean(img, i, j, w_size);
			w_v = w_var(img, i, j, w_size, w_m);
			weight = (w_v) / (w_v + img_v);
			dest->vals[i][j] = 
				w_m + weight * (img->vals[i][j] - w_m);
		}
}

/*
 * calculates the mean of the pixels of img
 * of the window of size w_size x w_size centered at pixel [i,j]
 * ignores edges that cannot be center of window
 */
static float w_mean(const struct img *img, int i, int j, int w_size)
{
	/*
	 * total stores sum of values in window
	 * w_i w_j iterate current window in img
	 */
	int total, w_i, w_j;
	total = 0;
	for (w_i=i-w_size/2; w_i<=i+w_size/2; w_i++)
		for (w_j=j-w_size/2; w_j<=j+w_size/2; w_j++)
			total += img->vals[w_i][w_j];
	return (float) total / (w_size * w_size);
}

/*
 * calculates the variance of the pixels of img
 * of the window of size w_size x w_size centered at pixel [i,j]
 * ignores edges that cannot be center of window
 */
static float w_var(const struct img *img, int i, int j, int w_size, 
			float w_mean)
{
	/*
	 * total stores sum (pixel[i][j] - mean)^2 for each pixel in window 
	 * w_i w_j iterate current window in img
	 */
	float total;
	int w_i, w_j;
	total = 0;
	for (w_i=i-w_size/2; w_i<=i+w_size/2; w_i++)
		for (w_j=j-w_size/2; w_j<=j+w_size/2; w_j++)
			total += pow(img->vals[w_i][w_j] - w_mean, 2);
	return total / (img->max + 1);
}

/*
 * returns the mean of all the pixels in img 
 */
static float img_mean(const struct img *img)
{
	float total;
	int i, j;
	total = 0;
	for (i=0; i<img->rows; i++)
		for(j=0; j<img->cols; j++)
			total += img->vals[i][j];
	return total / (img->rows * img->cols);
}

/*
 * returns the variance of all the pixels in img
 */
static float img_var(const struct img *img, float img_mean)
{
	float total;
	int i, j;
	total = 0;
	for (i=0; i<img->rows; i++)
		for(j=0; j<img->cols; j++)
			total += pow(img->vals[i][j] - img_mean, 2);
	return total / (img->max + 1);
}
