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
	struct image *smimg, *img, *gx, *gy, *l, *gx2, *gy2, *pMalik;
	struct image *pMalikConstant, *pMalikDiff;
	
	if (argc != 2)
		ERROR("no image specified\n");
	

	imgp = argv[1];

	img = read_image(imgp);
	smimg = convolve(img,3,3,gaussian_3_3_kernel, (1.0f/16));   
	write_image(smimg, "../images/smooth.pgm");
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

//	print_image(gx);
	
	struct float_image *fi = convert_to_float(l);
	//print_float_image(fi);

	free_image(gx);
	free_image(gy);
	free_image(gx2);
	free_image(gy2);
	free_image(l);
	
	pMalik = run_perona_malik(img, 10, 1, 25, .25);
	write_image(pMalik, "../images/pmalik.pgm");
	
	//pMalikConstant = run_perona_malik_constant(img, 0.125, 4);
//	write_image(pMalikConstant, "../images/pConstant.pgm");
	
	pMalikDiff = run_perona_malik_fdiff(img, 10000, 1, 100);
	write_image(pMalikDiff, "../images/pMalikFD.pgm");

	fi = convert_to_float(img);
	struct float_image *pMalikDiffFloat;
	pMalikDiffFloat = run_perona_malik_fdiff_float(img, 8, 24, 0.25); 
//	print_float_image(pMalikDiffFloat);
	pMalik = convert_to_pgm(pMalikDiffFloat);
	//print_image(pMalik);
	write_image(pMalik, "../images/pMalikFloat.pgm");
	free_image(img);
	
	free_image(pMalikDiff);
//	free_image(pMalikConstant);
	free_image(pMalik);
	
	return EXIT_SUCCESS;
}
