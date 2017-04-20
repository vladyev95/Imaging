#include "anisotropic.h"


static const float K = 0.35f;

static int16_t **gradient_y(const struct image *img);
static int16_t gradient_y_val(const struct image *img, int i, int j);
static int16_t **gradient_x(const struct image *img);
static int16_t gradient_x_val(const struct image *img, int i, int j);

static int16_t **laplace(const struct image *img);
static int16_t laplace_val(const struct image *img, int i, int j);

static int16_t **gradient_y(const struct image *img)
{
	uint16_t **grad_y;
	int i, j;
	if (!(grad_y = malloc(sizeof(laplace[0]) * img->rows)))
		ERROR("malloc()");
	for (i=0;i<img->rows;i++)
		if (!(grad_y[i] = malloc(sizeof(laplace[i][0]) * img->cols)))
			ERROR("malloc()");
	for (i=0;i<img->rows;i++)
		for (j=0;j<img->cols;j++)
			grad_y[i][j] = gradient_y_val(img, i, j);
	return gradient_y;
}

static int16_t gradient_y_val(const struct image *img, int i, int j)
{
	int16_t val;
	val = 0;
	if (i != img->rows)
		val += ((int16_t)img->values[i+1][j]) - img->values[i][j]; 
	return val;
}



static int16_t **gradient_x(const struct image *img)
{
	uint16_t **grad_x;
	int i, j;
	if (!(grad_x = malloc(sizeof(laplace[0]) * img->rows)))
		ERROR("malloc()");
	for (i=0;i<img->rows;i++)
		if (!(grad_x[i] = malloc(sizeof(laplace[i][0]) * img->cols)))
			ERROR("malloc()");
	for (i=0;i<img->rows;i++)
		for (j=0;j<img->cols;j++)
			grad_x[i][j] = gradient_x_val(img, i, j);
	return gradient_x;
}


static int16_t gradient_x_val(const struct image *img, int i, int j)
{
	int16_t val;
	val = 0;
	if (j != img->cols)
		val += ((int16_t)img->values[i][j+1]) - img->values[i][j]; 
	return val;
}


static int16_t **laplace(const struct image *img)
{
	uint16_t **laplace;
	int i, j;
	if (!(laplace = malloc(sizeof(laplace[0]) * img->rows)))
		ERROR("malloc()");
	for (i=0;i<img->rows;i++)
		if (!(laplace[i] = malloc(sizeof(laplace[i][0]) * img->cols)))
			ERROR("malloc()");
	for (i=0;i<img->rows;i++)
		for (j=0;j<img->rows;j++)
			laplace[i][j] = laplace_val(img, i, j);
	return laplace;
}


static int16_t laplace_val(const struct image *img, int i, int j)
{
	int16_t val;
	val = 0;
	if (i != 0)
		val += img->values[i-1][j];
	if (i != img->rows)
		val += img->values[i+1][j];
	if (j != 0)
		val += img->values[i][j-1];
	if (j != img->cols)
		val += img->values[i][j+1];
	val -= 4 * ((int16_t)img->values[i][j]);
	return val;
}
