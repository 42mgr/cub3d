/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:47:34 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/15 19:00:58 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks if only 1 or 0 can be found around the current positon ('1')
 * If not, the maze is not closed and the flood fill algorithm will fail
*/
int	check_around(t_data *data, int dxy[2][8], int x, int y)
{
	int				i;
	int				nx;
	int				ny;

	i = 0;
	while (i < 8)
	{
		nx = x + dxy[0][i];
		ny = y + dxy[1][i];
		box_min_max(data, nx, ny);
		//printf("dim.max_y: %i\n", data->dim.max_y);
		if (data->dim.max_y > ny)
		{
			if (data->maze_cpy[ny][nx] != '0' && data->maze_cpy[ny][nx] != '1')
				return (1);
			else
				i++;
		}
		else
			i++;
	}
	return (0);
}

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

 	printf("[y][x]: %c, y: %i, x: %i maxy: %i, max_x: %i\n", data->maze_cpy[y][x], y, x, data->dim.max_y, data->dim.max_x);
	print_all(data->maze_cpy, 21);
	if ((data->dim.max_y < y && data->dim.max_y >= 0) || (data->dim.max_x < x && data->dim.max_x >= 0))
		return (++error);
	else if (data->maze_cpy[y][x] == '1')
		return (0);
	else if (data->maze_cpy[y][x] == '0')
	{
		data->maze_cpy[y][x] = '1';
		if (check_around(data, dxy, x, y))
			return (++error);
	}
	i = 0;
	while (i < 8)
	{
		nx = x + dxy[0][i];
		ny = y + dxy[1][i];
		if (data->dim.max_y < ny || data->dim.max_x < nx || ny < 0 || nx < 0)
			return (++error);
		run_fill(data, dxy, nx, ny);
		i++;
	}
	return (error);
}

void	mm_draw_floor(t_data *data, int y, int x)
{
	if (x > (data->dim.max_x - data->dim.min_x + 1))
		return ;
	data->maze_cpy[y][x] = '1';
}

void	mm_draw_objects(t_data *data, int y, int x)
{
	if (x > (data->dim.max_x - data->dim.min_x + 1))
		return ;
	if (data->maze[y + data->dim.min_y][x + data->dim.min_x] == '1')
	{
		data->maze_cpy[y][x] = '1';
	}
	else if (data->maze[y + data->dim.min_y][x + data->dim.min_x] == '0')
	{
		data->maze_cpy[y][x] = '0';
	}
}

int	put_err(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
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
		ret = put_err("\e[1;41mError\e[0m\n\tMalloc failed for maze copy\n");
	if (data->start.x == -1 || data->start.y == -1)
		ret = put_err("\e[1;41mError\e[0m\n\tNo start position detected.\n");
	if (ret == 0)
	{
		ret = run_fill(data, dxy, data->start.x, data->start.y);
		if (ret != 0)
			ft_putstr_fd("\e[1;41mError\e[0m\n\tMaze is not closed\n", 2);
		if (ret == 0)
		{
			free_2d_array(data->maze_cpy);
			create_clean_maze(data);
		}
	}
	return (ret);
}
