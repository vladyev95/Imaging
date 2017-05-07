#include "kernels.h"

int identity_kern[IDENTITY_ROWS * IDENTITY_COLS] = 
{ 0, 0, 0,
  0, 1, 0,
  0, 0, 0 };

int box_blur_kern[BOX_BLUR_ROWS * BOX_BLUR_COLS] = 
{ 1, 1, 1,
  1, 1, 1,
  1, 1, 1 };

int edge_1_kern[EDGE_1_ROWS * EDGE_1_COLS] = 
{ 1, 0, -1,
  0, 0, 0,
  -1, 0, 1 };


int edge_2_kern[EDGE_2_ROWS * EDGE_2_COLS] = 
{ 0, 1, 0,
  1, -4, 1,
  0, 1, 0 };


int edge_3_kern[EDGE_3_ROWS * EDGE_3_COLS] =
{ -1, -1, -1,
  -1, 8, -1,
  -1, -1, -1 };

int sharpen_kern[SHARPEN_ROWS * SHARPEN_COLS] =
{ 0, -1, 0,
  -1, 5, -1,
  0, -1, 0 };

int gauss_3_3_kern[GAUSS_3_3_ROWS * GAUSS_3_3_COLS] =
{ 1, 2, 1,
  2, 4, 2,
  1, 2, 1 };

int gauss_5_5_kern[GAUSS_5_5_ROWS * GAUSS_5_5_COLS] =
{ 1, 4, 6, 4, 1,
  4, 16, 24, 16, 4,
  6, 24, 36, 24, 6,
  4, 16, 24, 16, 4,
  1, 4, 6, 4, 1 };

int xffdiff_kern[XFFDIFF_ROWS * XFFDIFF_COLS] =
{ 0, 0, 0,
  0, -1, 1,
  0, 0, 0 };

int xfbdiff_kern[XFBDIFF_ROWS * XFBDIFF_COLS] =
{ 0, 0, 0,
  -1, 1, 0,
  0, 0, 0 };

int yffdiff_kern[YFFDIFF_ROWS * YFFDIFF_COLS] =
{ 0, 0, 0,
  0, -1, 0,
  0, 1, 0 };

int yfbdiff_kern[YFBDIFF_ROWS * YFBDIFF_COLS] =
{ 0, -1, 0,
  0, 1, 0,
  0, 0, 0 };

int laplacian_kern1[LAPLACIAN_ROWS * LAPLACIAN_COLS] =
{ 0, -1, 0,
  -1, 4, -1,
  0, -1, 0 };

int laplacian_kern2[LAPLACIAN_ROWS * LAPLACIAN_COLS] =
{ -1, -1, -1,
  -1, 8, -1,
  -1, -1, -1 };
