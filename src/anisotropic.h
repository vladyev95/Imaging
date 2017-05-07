#ifndef ANISOTROPIC_H
#define ANISOTROPIC_H

#include "img.h"

void perona_malik(struct img *dest, struct img *img, float lambda, float k, 
		int exp, int iterations);

#endif
