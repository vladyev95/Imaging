#include <math.h>
#include <stdlib.h>
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

struct image *compute_c_exponential(const struct image *grad_x,
	const struct image *grad_y, int param_k)
{
		//Should check if grad_x and grad_y are same size?
		struct image *c_matrix = new_image(grad_x->rows, grad_x->cols, 
			grad_x->maxval);
		int row, col;
		
		for (row = 0; row < c_matrix->rows; row++){
			for (col = 0; col < c_matrix->cols; col++){
				c_matrix->values[row][col] = 
					compute_c_val_exp(grad_x->values[row][col], 
					grad_y->values[row][col], param_k); 
			}
		}

	//Note: This will need to be freed at a later date.
	return c_matrix;

}

struct image *compute_c_division(const struct image *grad_x,
	const struct image *grad_y, int param_k)
{
		//Should check if grad_x and grad_y are same size?
		struct image *c_matrix = new_image(grad_x->rows, grad_x->cols, 
			grad_x->maxval);
		int row, col;
		
		for (row = 0; row < c_matrix->rows; row++){
			for (col = 0; col < c_matrix->cols; col++){
				c_matrix->values[row][col] = 
					compute_c_val_div(grad_x->values[row][col], 
					grad_y->values[row][col], param_k); 
			}
		}

	//Note: This will need to be freed at a later date.
	return c_matrix;

}

double compute_c_val_exp(int grad_x, int grad_y, int param_k)
{
	double grad_magnitude = 0;
	grad_magnitude = (grad_x * grad_x) + (grad_y * grad_y);
	return exp(-grad_magnitude / (param_k * param_k));
}

double compute_c_val_div(int grad_x, int grad_y, int param_k)
{
	double grad_magnitude = 0;
	grad_magnitude = (grad_x * grad_x) + (grad_y * grad_y);
	return 1.0 / (1 + (grad_magnitude / (param_k * param_k)));
}

struct image *compute_dI(const struct image *original_image, int param_k,
	int expFlag)
{
	struct image *grad_x;
	struct image *grad_y;
	struct image *c_matrix;
	struct image *grad_c_x;
	struct image *grad_c_y;
	struct image *laplacian_matrix;
	struct image *dI = new_image(original_image->rows, original_image->cols, original_image->maxval);

	int row, col;

	grad_x = gradient_x(original_image);
	grad_y = gradient_y(original_image);
	laplacian_matrix = laplace(original_image);
	
	if (expFlag) 
		c_matrix = compute_c_exponential(grad_x, grad_y, param_k);
	else
		c_matrix = compute_c_division(grad_x, grad_y, param_k);

	grad_c_x = gradient_x(c_matrix);
	grad_c_y = gradient_y(c_matrix);
	
	for (row = 0; row < dI->rows; row++){
		for (col = 0; col < dI->cols; col++){
			//I leave out the division by dx or dy since they == 1.
			dI->values[row][col] =
				(grad_c_x->values[row][col] * grad_x->values[row][col])	+
				(grad_c_y->values[row][col] * grad_y->values[row][col]) +
				(c_matrix->values[row][col] * 
					laplacian_matrix->values[row][col]);
		}
	}

	free(grad_c_x);
	free(grad_c_y);
	free(laplacian_matrix);
	free(c_matrix);
	free(grad_x);
	free(grad_y);

	//Will have to be freed later.
	return dI;
}

struct image *run_perona_malik(const struct image *orig_image, 
	const int param_k, const int expFlag, const int iterations,
	const float learning_param)
{
	int i;
	struct image *dI;
	struct image *time_t_image;
	struct image *updated_image;
	struct image *scalar_mult_result;

	time_t_image = copy_image(orig_image);

	for (i = 0; i < iterations; i++){
		dI = compute_dI(orig_image, param_k, expFlag);
		scalar_mult_result = scalar_mult(dI, learning_param);
		//Need to free time_t_image in between calls?
		time_t_image = add_image(time_t_image, scalar_mult_result);
		free(dI);
		free(scalar_mult_result);
	}

	return time_t_image;
}
