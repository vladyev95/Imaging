#ifndef ANISOTROPIC_H
#define ANISOTROPIC_H


struct image *gradient_y(const struct image *img);

struct image *gradient_x(const struct image *img);

struct image *gradient2_y(const struct image *img);

struct image *gradient2_x(const struct image *img);

struct image *laplace(const struct image *img);

#endif
