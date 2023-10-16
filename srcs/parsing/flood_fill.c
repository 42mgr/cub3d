/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:47:34 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/16 16:59:33 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Recursive flood fill algorithm
 * Fills in all 8 directions, to even fill a 0 in an exposed corner
*/
int	run_fill(t_data *data, int dxy[2][8], int x, int y)
{
	static int	error = 0;
	int			i;
	int			nx;
	int			ny;

	if (valid_i(data, x, y) != 0)
		return (++error);
	if (data->maze_cpy[y][x] == '1')
		return (0);
	else if (data->maze_cpy[y][x] == '0')
	{
		if (check_around(data, dxy, x, y))
			return (++error);
	}
	i = 0;
	while (i < 8)
	{
		nx = x + dxy[0][i];
		ny = y + dxy[1][i];
		if (valid_i(data, nx, ny) != 0)
			return (++error);
		run_fill(data, dxy, nx, ny);
		i++;
	}
	return (error);
}

/**
 * returns 0 if the index is valid (meaning it's in the allocated area)
 * returns 1 or 2 on error
*/
int	valid_i(t_data *data, int x, int y)
{
	if (y < 0 || x < 0)
		return (1);
	if (y >= data->maze_number_of_lines)
		return (2);
	if (x >= data->maze_cpy_dim[y])
		return (3);
	return (0);
}

int	set_maze_cpy_dim(t_data *data)
{
	int	i;

	i = 0;
	while (data->maze_cpy[i])
		i++;
	data->maze_number_of_lines = i;
	data->maze_cpy_dim = malloc(sizeof(int) * i);
	if (data->maze_cpy_dim == NULL)
	{
		ft_putstr_fd("\e[1;41mError\e[0m\n\tmaze cpy dim alloc failed\n", 2);
		return (1);
	}
	i = 0;
	while (data->maze_cpy[i])
	{
		data->maze_cpy_dim[i] = ft_strlen(data->maze_cpy[i]);
		i++;
	}
	return (0);
}

int	start_fill(t_data *data, int dxy[2][8])
{
	int	ret;

	ret = 0;
	ret = run_fill(data, dxy, data->start.x, data->start.y);
	if (ret != 0)
		ft_putstr_fd("\e[1;41mError\e[0m\n\tMaze is not closed\n", 2);
	free_2d_array(data->maze_cpy);
	create_clean_maze(data);
	return (ret);
}

/**
 * The main function to check if the maze is closed
*/
int	flood_fill(t_data *data)
{
	int		ret;
	int		dxy[2][8];

	create_dxy(dxy);
	ret = 0;
	data->maze_cpy = duplicate_maze(data->dim.lines, data->maze);
	if (!data->maze_cpy)
	{
		ft_putstr_fd("\e[1;41mError\e[0m\n\tMalloc failed for maze copy\n", 2);
		ret = 1;
	}
	if (data->start.x == -1 || data->start.y == -1)
	{
		ret = 1;
		ft_putstr_fd("\e[1;41mError\e[0m\n\tNo start position detected.\n", 2);
	}
	if (ret == 0)
		ret = set_maze_cpy_dim(data);
	if (ret == 0)
		ret = start_fill(data, dxy);
	return (ret);
}
