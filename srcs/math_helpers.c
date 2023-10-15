/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:45:52 by fheld             #+#    #+#             */
/*   Updated: 2023/10/14 17:49:03 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * converts the integer points to doubles and
 * calculates the distance from a to b in doubles
 * @param a fist point
 * @param b second point
*/
double	dist(t_int_p2 a, t_int_p2 b)
{
	double	ax;
	double	ay;
	double	bx;
	double	by;

	ax = a.x;
	ay = a.y;
	bx = b.x;
	by = b.y;
	return (sqrt(((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by))));
}
