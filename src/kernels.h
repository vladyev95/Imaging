#ifndef KERNELS_H
#define KERNELS_H


#define IDENTITY_KERNEL_ROWS 3
#define IDENTITY_KERNEL_COLS 3
#define IDENTITY_KERNEL_COEFF 1.0f

int identity_kernel[IDENTITY_KERNEL_ROWS][IDENTITY_KERNEL_COLS] =
{ {0, 0, 0},
  {0, 1, 0},
  {0, 0, 0} };


#define BOX_BLUR_KERNEL_ROWS 3
#define BOX_BLUR_KERNEL_COLS 3
#define BOX_BLUR_KERNEL_COEFF (1.0f/9)
int box_blur_kernel[BOX_BLUR_KERNEL_ROWS][BOX_BLUR_KERNEL_COLS] =
{ {1, 1, 1},
  {1, 1, 1},
  {1, 1, 1} };

#define EDGE_1_KERNEL_ROWS 3
#define EDGE_1_KERNEL_COLS 3
#define EDGE_1_KERNEL_COEFF 1.0f

int edge_1_kernel[EDGE_1_KERNEL_ROWS][EDGE_1_KERNEL_COLS] =
{ {1, 0, -1},
  {0, 0, 0},
  {-1, 0, 1} };


#define EDGE_2_KERNEL_ROWS 3
#define EDGE_2_KERNEL_COLS 3
#define EDGE_2_KERNEL_COEFF 1.0f

int edge_2_kernel[EDGE_2_KERNEL_ROWS][EDGE_2_KERNEL_COLS] =
{ {0, 1, 0},
  {1, -4, 1},
  {0, 1, 0} };


#define EDGE_3_KERNEL_ROWS 3
#define EDGE_3_KERNEL_COLS 3
#define EDGE_3_KERNEL_COEFF 1.0f

int edge_3_kernel[EDGE_3_KERNEL_ROWS][EDGE_3_KERNEL_COLS] =
{ {-1, -1, -1},
  {-1, 8, -1},
  {-1, -1, -1} };


#define SHARPEN_KERNEL_ROWS 3
#define SHARPEN_KERNEL_COLS 3
#define SHARPEN_KERNEL_COEFF 1.0f

int sharpen_kernel[SHARPEN_KERNEL_ROWS][SHARPEN_KERNEL_COLS] =
{ {0, -1, 0},
  {-1, 5, -1},
  {0, -1, 0} };


#define GAUSSIAN_3_3_KERNEL_ROWS 3
#define GAUSSIAN_3_3_KERNEL_COLS 3
#define GAUSSIAN_3_3_KERNEL_COEFF (1.0f/16)

int gaussian_3_3_kernel[GAUSSIAN_3_3_KERNEL_ROWS][GAUSSIAN_3_3_KERNEL_COLS] =
{ {1, 2, 1},
  {2, 4, 2},
  {1, 2, 1} };


#define GAUSSIAN_5_5_KERNEL_ROWS 5
#define GAUSSIAN_5_5_KERNEL_COLS 5
#define GAUSSIAN_5_5_KERNEL_COEFF (1.0f/256)

int gaussian_5_5_kernel[GAUSSIAN_5_5_KERNEL_ROWS][GAUSSIAN_5_5_KERNEL_COLS] =
{ {1, 4, 6, 4, 1},
  {4, 16, 24, 16, 4},
  {6, 24, 36, 24, 6},
  {4, 16, 24, 16, 4},
  {1, 4, 6, 4, 1} };

#endif
