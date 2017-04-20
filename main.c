#include <stdlib.h>
#include <stdio.h>
#include "lee_filter.h"
#include "kernels.h"
#include "noise.h"
#include "convolution.h"
#include "image.h"
#include "median_filter.h"

#define PATH "/home/vlad/Dropbox/s17/imaging/heart/heart.pgm"

int main(void)
{
	struct image *img, *median_img, *salty, *lee;
	
	img = read_image(PATH);
	salty = salt_n_pepper(img);
	median_img = median_filter(salty, 5);
	lee = lee_filter(img, 3);
			
	write_image(img, "heart.pgm");
	write_image(median_img, "heart_median.pgm");
	write_image(salty, "salty.pgm");
	write_image(lee, "lee.pgm");
	
	free_image(img);
	free_image(median_img);
	free_image(salty);
	free_image(lee);
	
	
	
	return EXIT_SUCCESS;
}
