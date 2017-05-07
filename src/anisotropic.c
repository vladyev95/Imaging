#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "anisotropic.h"
#include "kernels.h"
#include "maths.h"
#include "img.h"
#include "fimg.h"

static float c_exp_val(float gx, float g);
static float c_div_val(float gx, float g);
static void pm_iter(struct fimg *dest, const struct fimg *src, float lambda, 
		float k, int exp);
static void comp_c(struct fimg *dest, const struct fimg *grad, float k, 
		int exp);



static float c_exp_val(float g, float k)
{
	return exp(-powf(g / k, 2));
}

static float c_div_val(float g, float k)
{
	return 1 / ( 1 + powf(g / k, 2));
}

static void comp_c(struct fimg *dest, const struct fimg *grad, float k,
		int exp)
{
	int i, j;
	for (i=0; i<grad->rows; i++) {
		for (j=0; j<grad->cols;j++) {
			if (exp)
				dest->vals[i][j] = 
					c_exp_val(grad->vals[i][j], k);
			else
				dest->vals[i][j] = 
					c_div_val(grad->vals[i][j], k);
		}
	}
}

static void pm_iter(struct fimg *dest, const struct fimg *src, float lambda, 
		float k, int exp)
{
	int i, j;
	struct fimg cxf, cxb, cyf, cyb, gxf, gyf, gxb, gyb;
	init_fimg(&cxf, src->rows, src->cols, src->max);
	init_fimg(&cxb, src->rows, src->cols, src->max);
	init_fimg(&cyf, src->rows, src->cols, src->max);
	init_fimg(&cyb, src->rows, src->cols, src->max);
	init_fimg(&gxf, src->rows, src->cols, src->max);
	init_fimg(&gyf, src->rows, src->cols, src->max);
	init_fimg(&gxb, src->rows, src->cols, src->max);
	init_fimg(&gyb, src->rows, src->cols, src->max);

	cp_fimg(&gxf, src);
	cp_fimg(&gyf, src);
	cp_fimg(&gxb, src);
	cp_fimg(&gyb, src);

	correlate_fimg(&gxf, src, xffdiff_kern, 3, 3, 1);
	correlate_fimg(&gyf, src, yffdiff_kern, 3, 3, 1);
	correlate_fimg(&gxb, src, xfbdiff_kern, 3, 3, 1);
	correlate_fimg(&gyb, src, yfbdiff_kern, 3, 3, 1);

	comp_c(&cxf, &gxf, k, exp);
	free_fimg(&gxf);
	comp_c(&cxb, &gxb, k, exp);
	free_fimg(&gxb);
	comp_c(&cyf, &gyf, k, exp);
	free_fimg(&gyf);
	comp_c(&cyb, &gyb, k, exp);
	free_fimg(&gyb);

	for (i=1; i<src->rows-1; i++) {
		for (j=1; j<src->cols-1; j++) {
			dest->vals[i][j] = src->vals[i][j] + lambda *
			((cyb.vals[i][j] * 
				(src->vals[i-1][j] - src->vals[i][j])) +

			(cyf.vals[i][j] * 
				(src->vals[i+1][j] - src->vals[i][j])) +

			(cxf.vals[i][j] * 
				(src->vals[i][j+1] - src->vals[i][j])) +

			(cxb.vals[i][j] * 
				(src->vals[i][j-1] - src->vals[i][j])));
		}
	}
	free_fimg(&cxf);
	free_fimg(&cxb);
	free_fimg(&cyf);
	free_fimg(&cyb);
}

void perona_malik(struct img *dest, struct img *img, float lambda, float k, 
		int exp, int iterations)
{
	int i;
	struct fimg fsrc, fdest;
	init_fimg(&fsrc, img->rows, img->cols, img->max);
	init_fimg(&fdest, img->rows, img->cols, img->max);
	img2fimg(&fsrc, img);
	cp_fimg(&fdest, &fsrc);
	for (i=0; i<iterations; i++) {
		pm_iter(&fdest, &fsrc, lambda, k, exp);
		cp_fimg(&fsrc, &fdest);
	}
	fimg2img(dest, &fdest);
	free_fimg(&fsrc);
	free_fimg(&fdest);
}
