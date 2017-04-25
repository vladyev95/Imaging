#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <sys/types.h>

struct image *median_filter(const struct image *img, size_t w_size);

#endif
