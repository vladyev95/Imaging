#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "img.h"
#include "noise.h"


static bool seeded = false;

void salt_n_pepper(struct img *dest, const struct img *img)
{	
	int i, j, rand_val;
	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}
	for (i=0; i<img->rows; i++) {
		for (j=0; j<img->rows; j++) {
			rand_val = rand() % 11;
			if (rand_val == 10)
				dest->vals[i][j] = img->max;
			else if (rand_val == 0)
				dest->vals[i][j] = 0;
		}
	}
}
