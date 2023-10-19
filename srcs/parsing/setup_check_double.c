/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_check_double.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:05:09 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/19 15:25:49 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_double_rgb(char a, int *error)
{
	static int	f = 0;
	static int	c = 0;

	if (a == 'F' && f == 0)
		f++;
	else if (a == 'C' && c == 0)
		c++;
	else
	{
		ft_putstr_fd("\e[1;41mError\e[0m\n\tMore than one background color.\n", 2);
		*error = 2;
		return (2);
	}
	return (0);
}

int	check_double_texture(char c)
{
	static int	n = 0;
	static int	e = 0;
	static int	s = 0;
	static int	w = 0;

	if (c == 'N' && n == 0)
		n++;
	else if (c == 'S' && s == 0)
		s++;
	else if (c == 'E' && e == 0)
		e++;
	else if (c == 'W' && w == 0)
		w++;
	else
	{
		ft_putstr_fd("\e[1;41mError\e[0m\n\tMore than one entry for texture.\n", 2);
		return (1);
	}
	return (0);
}
