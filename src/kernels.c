#include "kernels.h"

int identity_kernel[IDENTITY_KERNEL_ROWS][IDENTITY_KERNEL_COLS] =
{ {0, 0, 0},
  {0, 1, 0},
  {0, 0, 0} };

int box_blur_kernel[BOX_BLUR_KERNEL_ROWS][BOX_BLUR_KERNEL_COLS] =
{ {1, 1, 1},
  {1, 1, 1},
  {1, 1, 1} };

int edge_1_kernel[EDGE_1_KERNEL_ROWS][EDGE_1_KERNEL_COLS] =
{ {1, 0, -1},
  {0, 0, 0},
  {-1, 0, 1} };


int edge_2_kernel[EDGE_2_KERNEL_ROWS][EDGE_2_KERNEL_COLS] =
{ {0, 1, 0},
  {1, -4, 1},
  {0, 1, 0} };


int edge_3_kernel[EDGE_3_KERNEL_ROWS][EDGE_3_KERNEL_COLS] =
{ {-1, -1, -1},
  {-1, 8, -1},
  {-1, -1, -1} };

int sharpen_kernel[SHARPEN_KERNEL_ROWS][SHARPEN_KERNEL_COLS] =
{ {0, -1, 0},
  {-1, 5, -1},
  {0, -1, 0} };

int gaussian_3_3_kernel[GAUSSIAN_3_3_KERNEL_ROWS][GAUSSIAN_3_3_KERNEL_COLS] =
{ {1, 2, 1},
  {2, 4, 2},
  {1, 2, 1} };

int gaussian_5_5_kernel[GAUSSIAN_5_5_KERNEL_ROWS][GAUSSIAN_5_5_KERNEL_COLS] =
{ {1, 4, 6, 4, 1},
  {4, 16, 24, 16, 4},
  {6, 24, 36, 24, 6},
  {4, 16, 24, 16, 4},
  {1, 4, 6, 4, 1} };

int gradient_x_kernel[GRADIENT_X_KERNEL_ROWS][GRADIENT_X_KERNEL_ROWS] =
{ {0, 0, 0},
  {-1, 0, 1},
  {0, 0, 0} };

int gradient_y_kernel[GRADIENT_Y_KERNEL_ROWS][GRADIENT_X_KERNEL_ROWS] =
{ {0, -1, 0},
  {0, 0, 0},
  {0, 1, 0 }};

int laplace_kernel[LAPLACE_KERNEL_ROWS][LAPLACE_KERNEL_COLS] =
{ {0, 1, 0},
  {1, -4, 1},
  {0, 1, 0} };
