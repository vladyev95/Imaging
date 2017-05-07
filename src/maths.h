#ifndef MATHS_H
#define MATHS_H

#include <sys/types.h>

void correlate_img(struct img *dest, const struct img *img, int *kernel,
			int rows, int cols, float coeff);

void correlate_fimg(struct fimg *dest, const struct fimg *fimg, int *kernel,
			int rows, int cols, float coeff);


#endif
