#ifndef ANISOTROPIC_H
#define ANISOTROPIC_H

struct image *gradient_y(const struct image *img);

struct image *gradient_x(const struct image *img);

struct image *gradient2_y(const struct image *img);

struct image *gradient2_x(const struct image *img);

struct image *finite_north(const struct image *img);

struct image *finite_south(const struct image *img);

struct image *finite_east(const struct image *img);

struct image *finite_west(const struct image *img);

struct float_image *finite_north_float(const struct float_image *img);

struct float_image *finite_south_float(const struct float_image *img);

struct float_image *finite_east_float(const struct float_image *img);

struct float_image *finite_west_float(const struct float_image *img);


struct image *laplace(const struct image *img);

struct image *compute_c_exp_finite(const struct image *finite_north, float k);

struct image *element_wise_mult(const struct image *img1, const struct image *img2);

struct float_image *element_wise_mult_float(const struct float_image *img1, 
	const struct float_image *img2);

struct image *compute_c_exp_s(const struct image *finite_south);

struct image *compute_c_exp_e(const struct image *finite_east);

struct image *compute_c_exp_w(const struct image *finite_west);

struct image *compute_c_exponential(const struct image *grad_x, 
	const struct image *grad_y, int param_k);

struct image *compute_c_division(const struct image *grad_x,
	const struct image *grad_y, int param_k);

struct image *compute_dI(const struct image *original_image, int param_k,
	int expFlag);

struct image *run_perona_malik(const struct image *orig_image, 
	const int param_k, const int expFlag, const int iterations,
	const float learning_param);


struct image *run_perona_malik_constant(const struct image *orig_image,
	float const_param, int iterations);

struct image *run_perona_malik_fdiff(const struct image *img, float k,
	int iterations, float lambda);

struct float_image *run_perona_malik_fdiff_float(const struct image *img, float k,
	int iterations, float lambda);

double compute_c_val_exp(int grad_x, int grad_y, int param_k);

double compute_c_val_div(int grad_x, int grad_y, int param_k);

#endif

