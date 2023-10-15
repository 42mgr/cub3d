/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:26:01 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 18:20:57 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Prints the entire file to the terminal for debugging
*/
void	print_all(char **maze, int lines)
{
	int	x;
	int	y;

	y = 0;
	while (y < lines)
	{
		x = 0;
		while (maze[y][x])
		{
			ft_putchar_fd(maze[y][x], 2);
			x++;
		}
		ft_putchar_fd('\n', 2);
		y++;
	}
}

/**
 * Creates a duplicate of the enitre char **maze to be used for flood fill
*/
char	**duplicate_maze(int lines, char **maze)
{
	int		x;
	int		len;
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!copy)
		return (NULL);
	x = 0;
	(void)len;
	len = 0;
	while (maze[x])
	{
		len = ft_strlen(maze[x]);
		copy[x] = ft_strdup(maze[x]);
		x++;
	}
	copy[x] = NULL;
	return (copy);
}

/**
 * Function to keep track of area the flood fill algorithm is running
 * useful to check for newlines omitted by ft_split and drawing the Minimap
*/
void	box_min_max(t_data *data, int x, int y)
{
	if (data->dim.min_x == -1 || data->dim.min_x > x)
		data->dim.min_x = x;
	if (data->dim.max_x == -1 || data->dim.max_x < x)
		data->dim.max_x = x;
	if (data->dim.min_y == -1 || data->dim.min_y > y)
		data->dim.min_y = y;
	if (data->dim.max_y == -1 || data->dim.max_y < y)
		data->dim.max_y = y;
}

/**
 * 2D array with all numbers to calculate the 8 directions
 * manually initialzed (Norminette)
*/
void	create_dxy(int dxy[2][8])
{
	dxy[0][0] = 1;
	dxy[0][1] = -1;
	dxy[0][2] = 0;
	dxy[0][3] = 0;
	dxy[0][4] = 1;
	dxy[0][5] = 1;
	dxy[0][6] = -1;
	dxy[0][7] = -1;
	dxy[1][0] = 0;
	dxy[1][1] = 0;
	dxy[1][2] = 1;
	dxy[1][3] = -1;
	dxy[1][4] = 1;
	dxy[1][5] = -1;
	dxy[1][6] = 1;
	dxy[1][7] = -1;
}

int	create_clean_maze(t_data *data)
{
	int		y;
	int		x;
	int		i;

	y = data->dim.max_y - data->dim.min_y + 1;
	x = data->dim.max_x - data->dim.min_x + 1;
	data->maze_cpy = (char **)malloc(sizeof(char *) * (y + 1));
	if (!data->maze_cpy)
		return (1);
	data->maze_cpy[y] = NULL;
	i = 0;
	while (i < y)
	{
		data->maze_cpy[i] = (char *)malloc(sizeof(char) * x + 1);
		if (!data->maze_cpy[i])
			return (1);
		data->maze_cpy[i][x] = '\0';
		i++;
	}
	check_for_tile(data, mm_draw_floor);
	check_for_tile(data, mm_draw_objects);
	return (0);
}
