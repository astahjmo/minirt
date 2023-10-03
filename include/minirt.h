/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:09:38 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/10/03 11:48:37 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>

# define EPSILON 1e-6
# define X 0
# define Y 1
# define Z 2
# define R 0
# define G 1
# define B 2
# define W 3
# define VECTOR 0
# define POINT 1
# define COLOR 2
# define FALSE 0
# define TRUE 1

typedef float			t_tuple[4];
typedef float			t_3x3_row[3];
typedef float			t_2x2_row[2];
typedef unsigned short	t_bool;

typedef struct s_canvas {
	unsigned short	width;
	unsigned short	height;
	t_tuple			**pixels;
}				t_canvas;

typedef struct s_matrix {
	t_tuple		row_1;
	t_tuple		row_2;
	t_tuple		row_3;
	t_tuple		row_4;
}				t_matrix;

typedef struct s_2x2matrix {
	t_2x2_row	row_1;
	t_2x2_row	row_2;
}				t_2x2_matrix;

typedef struct s_3x3matrix {
	t_3x3_row	row_1;
	t_3x3_row	row_2;
	t_3x3_row	row_3;
}				t_3x3_matrix;

void		create_point(t_tuple tuple);
void		create_vector(t_tuple tuple);
t_bool		floats_eq(float a, float b);
void		add_tuples(const t_tuple a, const t_tuple b, t_tuple result);
void		subtract_tuples(const t_tuple a, const t_tuple b, t_tuple result);
void		negate_tuple(const t_tuple a, t_tuple result);
void		multiply_tuple_by_scalar(const t_tuple a, const float s, t_tuple r);
void		multiply_colors(const t_tuple c1, const t_tuple c2, t_tuple result);
t_bool		floats_eq(float a, float b);
float		magnitude(const t_tuple vec);
short		normalize(const t_tuple vec, t_tuple result);
short		cross(const t_tuple a, const t_tuple b, t_tuple cross_product);
t_canvas	create_canvas(unsigned short width, unsigned short height);
void		write_pixel(t_canvas *canvas, int x, int y, const t_tuple pixel);
char		*canvas_to_ppm(const t_canvas *canvas);
void		destroy_canvas(const t_canvas *canvas);
t_bool		tuples_neq(const t_tuple result, const t_tuple expected);
t_matrix	mult_matrices(t_matrix a, t_matrix b);
t_bool		matrices_eq(t_matrix a, t_matrix b);
float		dot(const t_tuple a, const t_tuple b);
#endif
