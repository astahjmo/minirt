/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tuples.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:27:15 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/10/14 17:49:30 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_point(t_tuple tuple)
{
	tuple[X] = 0;
	tuple[Y] = 0;
	tuple[Z] = 0;
	tuple[W] = POINT;
}

void	create_vector(t_tuple tuple)
{
	tuple[X] = 0;
	tuple[Y] = 0;
	tuple[Z] = 0;
	tuple[W] = VECTOR;
}
