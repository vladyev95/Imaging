#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "my_error.h"
#include "lee_filter.h"
#include "kernels.h"
#include "noise.h"
#include "convolution.h"
#include "image.h"
#include "median_filter.h"
#include "anisotropic.h"


/*
 * turns "/path/to/file" into "/path/to/file_type", places in buf
 */
void write_path(char *buf, const char *imgp, const char *type)
{
	strcpy(buf, imgp);
	strcat(buf, "_");
	strcat(buf, type);
	strcat(buf, ".pgm");
}

int main(int argc, char *argv[])
{
	char *imgp, buf[256];
	struct image *img, *smooth, *gx, *gy, *gx2, *gy2, *l,
			*smooth_gx, *smooth_gy, *smooth_l, *smooth_gx2,
			*smooth_gy2;

	if (argc != 2)
		ERROR("no image specified\n");
	

	imgp = argv[1];
	img = read_image(imgp);
	imgp[strlen(imgp) - 4] = '\0';
	smooth = convolve(img, 3, 3, gaussian_3_3_kernel, 
			GAUSSIAN_3_3_KERNEL_COEFF);
	gx = gradient_x(img);
	gy = gradient_y(img);
	gx2 = gradient2_x(img);
	gy2 = gradient2_y(img);
	l = laplace(img);

	smooth_gx = gradient_x(smooth);
	smooth_gy = gradient_y(smooth);
	smooth_l = laplace(smooth);
	smooth_gx2 = gradient2_x(smooth);
	smooth_gy2 = gradient2_y(smooth);

			
	write_path(buf, imgp, "smooth");
	write_image(smooth, buf);
	
	write_path(buf, imgp, "gx");
	write_image(gx, buf);

	write_path(buf, imgp, "gy");
	write_image(gy, buf);

	write_path(buf, imgp, "gx2");
	write_image(gx2, buf);

	write_path(buf, imgp, "gy2");
	write_image(gy2, buf);

	write_path(buf, imgp, "l");
	write_image(l, buf);

	write_path(buf, imgp, "smooth_gx");
	write_image(smooth_gx, buf);

	write_path(buf, imgp, "smooth_gy");
	write_image(smooth_gy, buf);

	write_path(buf, imgp, "smooth_l");
	write_image(smooth_l, buf);

	write_path(buf, imgp, "smooth_gx2");
	write_image(smooth_gx2, buf);

	write_path(buf, imgp, "smooth_gy2");
	write_image(smooth_gy2, buf);
	
	free_image(img);
	free_image(gx);
	free_image(gy);
	free_image(gx2);
	free_image(gy2);
	free_image(l);
	
	
	
	return EXIT_SUCCESS;
}
