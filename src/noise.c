#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "image.h"
#include "noise.h"


static bool seeded = false;

struct image *salt_n_pepper(const struct image *img)
{	
	struct image *new_img;
	int i, j, rand_val;
	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}
	new_img = copy_image(img);
	for (i=0;i<img->rows;i++)
		for (j=0;j<img->rows;j++) {
			rand_val = rand() % 11;
			if (rand_val == 10)
				new_img->values[i][j] = img->maxval;
			else if (rand_val == 0)
				new_img->values[i][j] = 0;
		}
	return new_img;
}
