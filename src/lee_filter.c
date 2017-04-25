#include <math.h>
#include <sys/types.h>
#include "image.h"
#include "lee_filter.h"

/*
 * calculates the mean of the pixels of img
 * of the window of size w_size x w_size centered at pixel [i,j]
 */
static float w_mean(const struct image *img, int i, int j, size_t w_size);

/*
 * calculates the variance of the pixels of img
 * of the window of size w_size x w_size centered at pixel [i,j]
 */
static float w_var(const struct image *img, int i, int j, size_t w_size,
		float w_mean);
		
/*
 * returns the mean of all the pixels in img 
 */
static float img_mean(const struct image *img);

/*
 * returns the variance of all the pixels in img 
 */
static float img_var(const struct image *img, float img_mean);


/*
 * applies the Lee image filter to the img
 * returns a new image that is the filtered version
 * w_size is the size of the kernel window to use
 * w_size must be odd, or unexpected behavior may occur
 */
struct image *lee_filter(const struct image *img, size_t w_size)
{
 	/* i j iterate img , w_s is w_size as int for loop logic to work */
	int i, j, w_s;
	/* w_m=w_mean w_v=w_var img_m=img_mean img_v=img_var */
	float w_m, w_v, img_m, img_v, weight;
	struct image *new_img;
	new_img = copy_image(img);
	w_s = w_size;
	img_m = img_mean(img);
	img_v = img_var(img, img_m);
	for (i=w_s/2;i<img->rows-w_s/2;i++)
		for (j=w_s/2;j<img->cols-w_s/2;j++) {
			w_m = w_mean(img, i, j, w_size);
			w_v = w_var(img, i, j, w_size, w_m);
			weight = (w_v) / (w_v + img_v);
			new_img->values[i][j] = 
				w_m + weight * 	(img->values[i][j] - w_m);
		}
		
	return new_img;
}

/*
 * calculates the mean of the pixels of img
 * of the window of size w_size x w_size centered at pixel [i,j]
 * ignores edges that cannot be center of window
 */
static float w_mean(const struct image *img, int i, int j, size_t w_size)
{
	/*
	 * total stores sum of values in window
	 * w_s is w_size as int to make loop logic work
	 * w_i w_j iterate current window in img
	 */
	int total, w_s, w_i, w_j;
	w_s = w_size;
	total = 0;
	for (w_i=i-w_s/2;w_i<=i+w_s/2;w_i++)
		for (w_j=j-w_s/2;w_j<=j+w_s/2;w_j++)
			total += img->values[w_i][w_j];
	return ((float) total) / (w_size * w_size);
}

/*
 * calculates the variance of the pixels of img
 * of the window of size w_size x w_size centered at pixel [i,j]
 * ignores edges that cannot be center of window
 */
static float w_var(const struct image *img, int i, int j, size_t w_size,
		float w_mean)
{
	/*
	 * total stores sum (pixel[i][j] - mean)^2 for each pixel in window 
	 * w_s is w_size as int to make loop logic work
	 * w_i w_j iterate current window in img
	 */
	float total;
	int w_s, w_i, w_j;
	w_s = w_size;
	total = 0;
	for (w_i=i-w_s/2;w_i<=i+w_s/2;w_i++)
		for (w_j=j-w_s/2;w_j<=j+w_s/2;w_j++)
			total += pow(img->values[w_i][w_j] - w_mean, 2);
	return total / (((int)img->maxval) + 1);
	
}

/*
 * returns the mean of all the pixels in img 
 */
static float img_mean(const struct image *img)
{
	float total;
	int i, j;
	total = 0;
	for (i=0;i<img->rows;i++)
		for(j=0;j<img->cols;j++)
			total += img->values[i][j];
	return total / (img->rows * img->cols);
}

/*
 * returns the variance of all the pixels in img
 */
static float img_var(const struct image *img, float img_mean)
{
	float total;
	int i, j;
	total = 0;
	for (i=0;i<img->rows;i++)
		for(j=0;j<img->cols;j++)
			total += pow(img->values[i][j] - img_mean , 2);
	return total / (((int)img->maxval) + 1);
}

