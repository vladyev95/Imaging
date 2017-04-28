#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "anisotropic.h"
#include "kernels.h"
#include "convolution.h"
#include "image.h"

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

struct image *finite_north(const struct image *img)
{
	return convolve(img, FINITE_NORTH_KERNEL_ROWS, FINITE_NORTH_KERNEL_COLS,
	finite_north_kernel, FINITE_NORTH_KERNEL_COEFF);
}

struct image *finite_south(const struct image *img)
{
	return convolve(img, FINITE_SOUTH_KERNEL_ROWS, FINITE_SOUTH_KERNEL_COLS,
	finite_south_kernel, FINITE_SOUTH_KERNEL_COEFF);
}

struct image *finite_east(const struct image *img)
{
	return convolve(img, FINITE_EAST_KERNEL_ROWS, FINITE_EAST_KERNEL_COLS,
		finite_east_kernel, FINITE_EAST_KERNEL_COEFF);

}

struct image *finite_west(const struct image *img)
{
	return convolve(img, FINITE_WEST_KERNEL_ROWS, FINITE_WEST_KERNEL_COLS,
		finite_west_kernel, FINITE_WEST_KERNEL_COEFF);

}

struct float_image *finite_north_float(const struct float_image *img)
{
	return convolve_float(img, FINITE_NORTH_KERNEL_ROWS, FINITE_NORTH_KERNEL_COLS,
	finite_north_kernel, FINITE_NORTH_KERNEL_COEFF);
}

struct float_image *finite_south_float(const struct float_image *img)
{
	return convolve_float(img, FINITE_SOUTH_KERNEL_ROWS, FINITE_SOUTH_KERNEL_COLS,
	finite_south_kernel, FINITE_SOUTH_KERNEL_COEFF);
}

struct float_image *finite_east_float(const struct float_image *img)
{
	return convolve_float(img, FINITE_EAST_KERNEL_ROWS, FINITE_EAST_KERNEL_COLS,
		finite_east_kernel, FINITE_EAST_KERNEL_COEFF);

}

struct float_image *finite_west_float(const struct float_image *img)
{
	return convolve_float(img, FINITE_WEST_KERNEL_ROWS, FINITE_WEST_KERNEL_COLS,
		finite_west_kernel, FINITE_WEST_KERNEL_COEFF);

}


struct image *compute_c_exp_finite(const struct image *f, float k)
{
	struct image *c_n;
	int i, j;
	float prod;
	c_n = new_image(f->rows, f->cols, f->maxval);
	
	for (i = 0; i < f->rows; i++){
		for (j = 0; j < f->rows; j++){
			prod = 
				(f->values[i][j] * f->values[i][j]) /
				(k * k);
				
			c_n->values[i][j] = exp((-1.0) * prod);
		}
	}
	return c_n;	
}

struct float_image *compute_c_exp_finite_float(const struct float_image *f, float k)
{
	struct float_image *c_n;
	int i, j;
	float prod;
	c_n = new_float_image(f->rows, f->cols, f->maxval);
	
	for (i = 0; i < f->rows; i++){
		for (j = 0; j < f->rows; j++){
			prod = 
				(f->values[i][j] * f->values[i][j]) /
				(k * k);
				
			c_n->values[i][j] = exp((-1.0) * prod);
		}
	}
	return c_n;	
}


struct image *laplace(const struct image *img)
{
	int row, col;
	struct image *grad_xx;
	struct image *grad_yy;
	struct image *laplace;

	laplace = new_image(img->rows, img->cols, img->maxval);

	grad_xx = gradient2_x(img);
	grad_yy = gradient2_y(img);

	for (row = 0; row < img->rows; row++){
			for (col = 0; col < img->cols; col++){
				laplace->values[row][col] = 
					(grad_xx->values[row][col] + 
					grad_yy->values[row][col])/ 4;
			}
	}
	
	return laplace;
	// return convolve(img, LAPLACE_KERNEL_ROWS, LAPLACE_KERNEL_COLS, 
	//		laplace_kernel, LAPLACE_KERNEL_COEFF);
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
	float prod;

	grad_x = gradient_x(original_image);
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
			prod =
				(grad_c_x->values[row][col] * grad_x->values[row][col])	+
				(grad_c_y->values[row][col] * grad_y->values[row][col]) +
				(c_matrix->values[row][col] * 
					laplacian_matrix->values[row][col]);
			if (prod > dI->maxval)
				dI->values[row][col] = dI->maxval;
			else if (prod < 0)
				dI->values[row][col] = 0;
			else
				dI->values[row][col] = prod;
		}
	}

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
		//print_image(dI);
		scalar_mult_result = scalar_mult(dI, learning_param);
		//Need to free time_t_image in between calls?
		time_t_image = add_image(time_t_image, scalar_mult_result);
		free_image(dI);
		free_image(scalar_mult_result);
	}

	return time_t_image;
}

struct image *run_perona_malik_constant(const struct image *orig_image,
	float const_param, int iterations)
{
	int i;
	struct image *dI;
	struct image *time_t_image;
	struct image *updated_image;
	struct image *laplacian_image;
	struct image *scal_res;

	laplacian_image = laplace(orig_image);

	time_t_image = copy_image(orig_image);
	for (i = 0; i < iterations; i++){
		scal_res = scalar_mult(laplacian_image, const_param);
		updated_image = add_image(scal_res, time_t_image);
		free_image(time_t_image);
		time_t_image = copy_image(updated_image);
		free_image(scal_res);	
	}

	return updated_image;

}

struct image *element_wise_mult(const struct image *img1,
	const struct image *img2)
{
	int i, j;
	struct image *r;
	
	r = new_image(img1->rows, img1->cols, img1->maxval);

	for (i = 0; i < r->rows; i++){
		for (j = 0; j < r->cols; j++){
			r->values[i][j] = img1->values[i][j] * img2->values[i][j];
			//printf("Img1 val: %d, Img2 val: %d\n", img1->values[i][j],
			//	img2->values[i][j]);
		}
	}
	
	return r;

}

struct float_image *element_wise_mult_float(const struct float_image *img1,
	const struct float_image *img2)
{
	int i, j;
	struct float_image *r;
	
	r = new_float_image(img1->rows, img1->cols, img1->maxval);

	for (i = 0; i < r->rows; i++){
		for (j = 0; j < r->cols; j++){
			r->values[i][j] = img1->values[i][j] * img2->values[i][j];
			//printf("Img1 val: %d, Img2 val: %d\n", img1->values[i][j],
			//	img2->values[i][j]);
		}
	}
	
	return r;

}

struct image *run_perona_malik_fdiff(const struct image *img, float k,
	int iterations, float lambda)
{
	struct image *dn, *ds, *de, *dw, *cn, *cs, *ce, *cw, *dI, *orig;
	struct image *cn_dn, *cs_ds, *cw_dw, *ce_de;
	int i, j, z;

	orig = copy_image(img);

	for (i = 0; i < iterations; i++){	
	
		dn = finite_north(orig);
//		print_image(dn);
//		printf("Done printing dn\n\n");
		ds = finite_south(orig);
		de = finite_east(orig);
		dw = finite_west(orig);

		cn = compute_c_exp_finite(dn, k);
//		print_image(cn);
//		printf("Done printing cn\n\n");
		cs = compute_c_exp_finite(ds, k);
		ce = compute_c_exp_finite(de, k);
		cw = compute_c_exp_finite(dw, k);

		cn_dn = element_wise_mult(cn, dn);
//		print_image(cn_dn);
		cs_ds = element_wise_mult(cs, ds);
		ce_de = element_wise_mult(ce, de);
		cw_dw = element_wise_mult(cw, dw);

		for (j = 0; j < orig->rows; j++){
			for (z = 0; z < orig->cols; z++){
//				printf("Before: %d\n", orig->values[j][z]);
				orig->values[j][z] = orig->values[j][z] +
					lambda * 
					(cn_dn->values[j][z] + cs_ds->values[j][z] +
					 cw_dw->values[j][z] + ce_de->values[j][z]);
//				printf("After: %d\n", orig->values[j][z]);
			}
		}

		free_image(dn);
		free_image(ds);
		free_image(dw);
		free_image(de);
		free_image(cn);
		free_image(cs);
		free_image(cw);
		free_image(ce);
		free_image(cn_dn);
		free_image(cs_ds);
		free_image(cw_dw);
		free_image(ce_de);
	}
	
	return orig;	

}

struct float_image *run_perona_malik_fdiff_float(const struct image *img, float k, int iterations, float lambda)
{

	struct float_image *dn, *ds, *de, *dw, *cn, *cs, *ce, *cw, *dI, *orig;
	struct float_image *cn_dn, *cs_ds, *cw_dw, *ce_de;
	int i, j, z;

	orig = convert_to_float(img);

	for (i = 0; i < iterations; i++){	
	
		dn = finite_north_float(orig);
//		print_image(dn);
//		printf("Done printing dn\n\n");
		ds = finite_south_float(orig);
		de = finite_east_float(orig);
		dw = finite_west_float(orig);

		cn = compute_c_exp_finite_float(dn, k);
//		print_image(cn);
//		printf("Done printing cn\n\n");
		cs = compute_c_exp_finite_float(ds, k);
		ce = compute_c_exp_finite_float(de, k);
		cw = compute_c_exp_finite_float(dw, k);

		cn_dn = element_wise_mult_float(cn, dn);
//		print_image(cn_dn);
		cs_ds = element_wise_mult_float(cs, ds);
		ce_de = element_wise_mult_float(ce, de);
		cw_dw = element_wise_mult_float(cw, dw);

		for (j = 0; j < orig->rows; j++){
			for (z = 0; z < orig->cols; z++){
//				printf("Before: %d\n", orig->values[j][z]);
				orig->values[j][z] = orig->values[j][z] +
					lambda * 
					(cn_dn->values[j][z] + cs_ds->values[j][z] +
					 cw_dw->values[j][z] + ce_de->values[j][z]);
//				printf("After: %d\n", orig->values[j][z]);
			}
		}

		free_float_image(dn);
		free_float_image(ds);
		free_float_image(dw);
		free_float_image(de);
		free_float_image(cn);
		free_float_image(cs);
		free_float_image(cw);
		free_float_image(ce);
		free_float_image(cn_dn);
		free_float_image(cs_ds);
		free_float_image(cw_dw);
		free_float_image(ce_de);
	}
	
	return orig;	

}
