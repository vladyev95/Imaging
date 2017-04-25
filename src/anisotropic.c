#include "anisotropic.h"
#include "kernels.h"
#include "convolution.h"
#include "image.h"


static const float K = 0.35f;

struct image *gradient_y(const struct image *img)
{
	return convolve(img, GRADIENT_Y_KERNEL_ROWS, GRADIENT_Y_KERNEL_COLS,
			gradient_y_kernel, GRADIENT_Y_KERNEL_COEFF);
}

struct image *gradient_x(const struct image *img)
{
	return convolve(img, GRADIENT_X_KERNEL_ROWS, GRADIENT_X_KERNEL_COLS,
			gradient_x_kernel, GRADIENT_X_KERNEL_COEFF);
}

struct image *gradient2_y(const struct image *img)
{
	struct image *img1, *img2;
	img1 = convolve(img, GRADIENT_Y_KERNEL_ROWS, GRADIENT_Y_KERNEL_COLS,
			gradient_y_kernel, GRADIENT_Y_KERNEL_COEFF);
	img2 = convolve(img1, GRADIENT_Y_KERNEL_ROWS, GRADIENT_Y_KERNEL_COLS,
			gradient_y_kernel, GRADIENT_Y_KERNEL_COEFF);
	free_image(img1);
	return img2;
}

struct image *gradient2_x(const struct image *img)
{
	struct image *img1, *img2;
	img1 = convolve(img, GRADIENT_X_KERNEL_ROWS, GRADIENT_X_KERNEL_COLS,
			gradient_x_kernel, GRADIENT_X_KERNEL_COEFF);
	img2 = convolve(img1, GRADIENT_X_KERNEL_ROWS, GRADIENT_X_KERNEL_COLS,
			gradient_x_kernel, GRADIENT_X_KERNEL_COEFF);
	free_image(img1);
	return img2;
}

struct image *laplace(const struct image *img)
{
	 return convolve(img, LAPLACE_KERNEL_ROWS, LAPLACE_KERNEL_COLS, 
			laplace_kernel, LAPLACE_KERNEL_COEFF);
}
