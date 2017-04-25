#include <stdlib.h>
#include <stdio.h>
#include "my_error.h"
#include "lee_filter.h"
#include "kernels.h"
#include "noise.h"
#include "convolution.h"
#include "image.h"
#include "median_filter.h"
#include "anisotropic.h"

int main(int argc, char *argv[])
{
	char *imgp;
	struct image *img, *gx, *gy, *l, *gx2, *gy2;

	if (argc != 2)
		ERROR("no image specified\n");

	imgp = argv[1];
	
	img = read_image(imgp);
	gx = gradient_x(img);
	gy = gradient_y(img);
	gx2 = gradient2_x(img);
	gy2 = gradient2_y(img);
	l = laplace(img);
			
	write_image(gx, "../images/gx.pgm");
	write_image(gy, "../images/gy.pgm");
	write_image(gx2, "../images/gx2.pgm");
	write_image(gy2, "../images/gy2.pgm");
	write_image(l, "../images/l.pgm");
	
	free_image(img);
	free_image(gx);
	free_image(gy);
	free_image(gx2);
	free_image(gy2);
	free_image(l);
	
	
	
	return EXIT_SUCCESS;
}
