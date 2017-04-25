#include <stdlib.h>
#include "median_filter.h"
#include "image.h"


static int cmp(const void *a, const void *b);

/*
 * uses window size of w_size x w_size
 * w_size must be an odd number
 */
struct image *median_filter(const struct image *img, size_t w_size)
{	
	/* w_vals = window values in current window */
	uint8_t w_vals[w_size * w_size];
	struct image *out;
	
	/* i j iterate img, w_i w_j iterate current window
	 * w_s is int w_size as int so that loop logic works
	 * w_cur is the next index in w_vals to fill
	 */
	int i, j, w_i, w_j, w_cur, w_s;
	
	w_s = w_size;
	out = copy_image(img);
	
	
	for (i=w_s/2;i<img->rows-w_s/2;i++) {
		for (j=w_s/2;j<img->cols-w_s/2;j++) {
			w_cur = 0;
			for (w_i=-w_s/2;w_i<=w_s/2;w_i++) {
				for (w_j=-w_s/2;w_j<=w_s/2;w_j++) {
					w_vals[w_cur++] = 
						img->values[i+w_i][j+w_j];
				}
			}
			qsort(w_vals, w_size * w_size, 
				sizeof(w_vals[0]), cmp);

			/* take median value of window */
			out->values[i][j] = w_vals[(w_size * w_size) / 2];
		}
	}
	return out;
}

/*
 * function for comparing the values of pixels in an image
 */
static int cmp(const void *a, const void *b)
{
	uint8_t x, y;
	x = *(uint8_t *) a;
	y = *(uint8_t *) b;
	if (x > y)
		return 1;
	else if (x < y)
		return -1;
	return 0;
}
