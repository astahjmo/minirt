#ifndef TEST_H
#define TEST_H

#include <criterion/criterion.h>
#include "minirt.h"
#include <stdio.h>
#define CYAN "\033[36m"
#define RED "\033[31m"
#define RESET "\033[0m"

typedef struct s_projectile {
    t_tuple position;
    t_tuple velocity;
} t_projectile;

typedef struct s_environment {
    t_tuple gravity;
    t_tuple wind;
} t_environment;

static inline void	print_tuple(const t_tuple a)
{
	printf("X: %f, Y: %f, Z: %f, W: %f\n", a[X], a[Y], a[Z], a[W]);
}

static inline void print_4x4matrix(const t_matrix a)
{
	print_tuple(a.row_1);
	print_tuple(a.row_2);
	print_tuple(a.row_3);
	print_tuple(a.row_4);
}

static inline t_bool cr_expect_tuple_eq(const t_tuple result, const t_tuple expected) { for (int i = 0; i < 4; i++) {
		cr_expect(floats_eq(result[i], expected[i]));
		if (!floats_eq(result[i], expected[i]))
			return (1);
	}
	return (0);
}

static inline void set_all_pixels_to_one_color(const t_canvas *c, t_tuple color) {
    for (int y = 0; y < c->height; y++)
        for (int x = 0; x < c->width; x++)
            write_pixel((t_canvas *)c, y, x, color);
}

static inline void create_ppm_file(t_constr ppm_string) {
	int fd = open("CANVAS.ppm", O_CREAT | O_RDWR);
	write(fd, ppm_string, strlen(ppm_string));
	close(fd);
}

static inline t_bool	cr_expect_matrices_eq(t_matrix a, t_matrix b)
{
	int	res;

	res = cr_expect_tuple_eq(a.row_1, b.row_1);
	res = cr_expect_tuple_eq(a.row_2, b.row_2);
	res = cr_expect_tuple_eq(a.row_3, b.row_3);
	res = cr_expect_tuple_eq(a.row_4, b.row_4);
	return (!res);
}

static inline int invert_axis(int size, float axis)
{
	return ((int)size - axis);
}

#define scenario1 CYAN \
"\nGiven point(0, 0, 0, POINT)\n"\
"And canvas(500, 500)\n" \
"And p ← translate_coordinate(point, canvas)\n " \
"Then p = point(250, 250, 0, POINT)\n"RESET

#endif
