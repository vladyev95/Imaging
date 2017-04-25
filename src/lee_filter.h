#ifndef LEE_FILTER_H
#define LEE_FILTER_H

#include <sys/types.h>

/*
 * applies the Lee image filter to the img
 * returns a new image that is the filtered version
 * w_size is the size of the kernel window to use
 * w_size must be odd, or unexpected behavior may occur
 */
struct image *lee_filter(const struct image *img, size_t w_size);


#endif
