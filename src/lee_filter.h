#ifndef LEE_FILTER_H
#define LEE_FILTER_H

#include "img.h"

/*
 * applies the Lee image filter to the img
 * w_size is the size of the kernel window to use
 * w_size must be odd, or unexpected behavior may occur
 */
void lee_filter(struct img *dest, const struct img *img, int w_size);


#endif
