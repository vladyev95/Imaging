#ifndef ANISOTROPIC_H
#define ANISOTROPIC_H


struct image *gradient_y(const struct image *img);

struct image *gradient_x(const struct image *img);

struct image *gradient2_y(const struct image *img);

struct image *gradient2_x(const struct image *img);

struct image *laplace(const struct image *img);

struct image *compute_c_exponential(const struct image *grad_x, 
	const struct image *grad_y, int param_k);

struct image *compute_c_division(const struct image *grad_x,
	const struct image *grad_y, int param_k);

struct image *compute_dI(const struct image *original_image, int param_k,
	int expFlag);

struct image *run_perona_malik(const struct image *orig_image, 
	const int param_k, const int expFlag, const int iterations,
	const float learning_param);

double compute_c_val_exp(int grad_x, int grad_y, int param_k);

double compute_c_val_div(int grad_x, int grad_y, int param_k);
#endif

