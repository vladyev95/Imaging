#ifndef KERNELS_H_INCLUDED
#define KERNELS_H_INCLUDED

#define IDENTITY_ROWS 3
#define IDENTITY_COLS 3
#define IDENTITY_COEFF 1.0
extern int identity_kern[IDENTITY_ROWS * IDENTITY_COLS];

#define BOX_BLUR_ROWS 3
#define BOX_BLUR_COLS 3
#define BOX_BLUR_COEFF (1.0f/9)
extern int box_blur_kern[BOX_BLUR_ROWS * BOX_BLUR_COLS];

#define EDGE_1_ROWS 3
#define EDGE_1_COLS 3
#define EDGE_1_COEFF 1.0
extern int edge_1_kern[EDGE_1_ROWS * EDGE_1_COLS];


#define EDGE_2_ROWS 3
#define EDGE_2_COLS 3
#define EDGE_2_COEFF 1.0
extern int edge_2_kern[EDGE_2_ROWS * EDGE_2_COLS];

#define EDGE_3_ROWS 3
#define EDGE_3_COLS 3
#define EDGE_3_COEFF 1.0
extern int edge_3_kern[EDGE_3_ROWS * EDGE_3_COLS];

#define SHARPEN_ROWS 3
#define SHARPEN_COLS 3
#define SHARPEN_COEFF 1.0
extern int sharpen_kern[SHARPEN_ROWS * SHARPEN_COLS];

#define GAUSS_3_3_ROWS 3
#define GAUSS_3_3_COLS 3
#define GAUSS_3_3_COEFF (1.0f/16)
extern int gauss_3_3_kern[GAUSS_3_3_ROWS * GAUSS_3_3_COLS];

#define GAUSS_5_5_ROWS 5
#define GAUSS_5_5_COLS 5
#define GAUSS_5_5_COEFF (1.0f/256)
extern int gauss_5_5_kern[GAUSS_5_5_ROWS * GAUSS_5_5_COLS];

/*
 * finite forward x
 */
#define XFFDIFF_ROWS 3
#define XFFDIFF_COLS 3
#define XFFDIFF_COEFF 1
extern int xffdiff_kern[XFFDIFF_ROWS * XFFDIFF_COLS];

/*
 * finite backward x
 */
#define XFBDIFF_ROWS 3
#define XFBDIFF_COLS 3
#define XFBDIFF_COEFF 1
extern int xfbdiff_kern[XFBDIFF_ROWS * XFBDIFF_COLS];

/*
 * finite forward y
 */
#define YFFDIFF_ROWS 3
#define YFFDIFF_COLS 3
#define YFFDIFF_COEFF 1
extern int yffdiff_kern[YFFDIFF_ROWS * YFFDIFF_COLS];

/*
 * finite backward y
 */
#define YFBDIFF_ROWS 3
#define YFBDIFF_COLS 3
#define YFBDIFF_COEFF 1
extern int yfbdiff_kern[YFBDIFF_ROWS * YFBDIFF_COLS];

#define LAPLACIAN_ROWS 3
#define LAPLACIAN_COLS 3
#define LAPLACIAN_COEFF 1
extern int laplacian_kern1[LAPLACIAN_ROWS * LAPLACIAN_COLS];

extern int laplacian_kern2[LAPLACIAN_ROWS * LAPLACIAN_COLS];

#endif
