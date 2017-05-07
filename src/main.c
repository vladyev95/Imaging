#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my_error.h"
#include "lee_filter.h"
#include "kernels.h"
#include "noise.h"
#include "maths.h"
#include "img.h"
#include "fimg.h"
#include "median_filter.h"
#include "anisotropic.h"

int main(int argc, char *argv[])
{
	char *imgp, buf[1024];
	struct img orig, pm;
	int i;
	
	if (argc != 2) {
		fprintf(stderr, "usage: ./%s img.pgm\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	

	imgp = argv[1];
	read_img(&orig, imgp);
	imgp[strlen(imgp) - 4] = 0;

	for (i=1;i<50;i++) {
		init_img(&pm, orig.rows, orig.cols, orig.max);
		perona_malik(&pm, &orig, .25, 5, 0, i);
		sprintf(buf, "%s_pm_%d.pgm", imgp, i);
		write_img(&pm, buf);
		free_img(&pm);
	}

	free_img(&orig);

	return EXIT_SUCCESS;
}
