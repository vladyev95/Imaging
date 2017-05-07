#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include "img.h"

void median_filter(struct img *dest, const struct img *img, int w_size);

#endif
