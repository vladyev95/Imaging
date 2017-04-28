#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <sys/types.h>

struct image *convolve(const struct image *img, size_t k_rows, size_t k_cols,
		int kernel[k_rows][k_cols], float coeff);

struct float_image *convolve_float(const struct float_image *img, size_t k_rows, size_t k_cols,
		int kernel[k_rows][k_cols], float coeff);


#endif
