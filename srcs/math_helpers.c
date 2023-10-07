/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:45:52 by fheld             #+#    #+#             */
/*   Updated: 2023/10/07 14:49:52 by fheld            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * converts the integer points to floats and
 * calculates the distance from a to b in floats
 * @param a fist point
 * @param b second point
*/
float	dist(t_int_p2 a, t_int_p2 b)
{
	float	ax;
	float	ay;
	float	bx;
	float	by;

	ax = a.x;
	ay = a.y;
	bx = b.x;
	by = b.y;
	return(sqrt(((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by))));
}