/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:47:34 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 18:36:57 by mgraf            ###   ########.fr       */
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
		if (data->maze_cpy[ny][nx] != '0' && data->maze_cpy[ny][nx] != '1')
			return (1);
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

	if (data->maze_cpy[y][x] == '1')
		return (0);
	else if (data->maze_cpy[y][x] == '0')
	{
		data->maze_cpy[y][x] = '1';
		if (check_around(data, dxy, x, y))
		{
			error = error + 1;
			return (1);
		}
	}
	i = 0;
	while (i < 8)
	{
		nx = x + dxy[0][i];
		ny = y + dxy[1][i];
		run_fill(data, dxy, nx, ny);
		i++;
	}
	return (error);
}

/* 	draw_picture(data->mlx42.mlx_ptr, data->mlx42.mm_black_img,
		(y * SPRITE_SIZE), (x * SPRITE_SIZE)); */
void	mm_draw_floor(t_data *data, int y, int x)
{
	if (x > (data->dim.max_x - data->dim.min_x + 1))
		return ;
	data->maze_cpy[y][x] = '1';
}

/* 		draw_picture(data->mlx42.mlx_ptr, data->mlx42.mm_grey_img,
			(y * SPRITE_SIZE), (x * SPRITE_SIZE)); */
/* 		draw_picture(data->mlx42.mlx_ptr, data->mlx42.mm_white_img,
			(y * SPRITE_SIZE), (x * SPRITE_SIZE)); */
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
	{
		ret = run_fill(data, dxy, data->start.x, data->start.y);
		if (ret != 0)
			ft_putstr_fd("\e[1;41mError\e[0m\n\tMaze is not closed\n", 2);
		free_2d_array(data->maze_cpy);
		create_clean_maze(data);
	}
	return (ret);
}

/* int	run_fill(t_data *data, char **maze, int x, int y)
{
	static int error = 0;
	int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
	int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};
	//int nx;
	//int	ny;

	if (maze[y][x] == '1' || maze[y][x] == '\0' || maze[y][x] == '\n')
	{
		if (maze[y][x] != '1')
			error++;
		return 0;
	}
	maze[y][x] = '1';
	for (int i = 0; i < 8; i++)
//	int i;
//	/i = 0;
//	while (i < 8)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (!maze[ny][nx] || maze[ny][nx] == '\0' || maze[ny][nx] == '\n')
		{
			error++;
			continue ;
		}
		if (maze[ny][nx] != '0' && maze[ny][nx] != '1')
		{
			error++;
			continue ;
		}
		run_fill(data, maze, nx, ny);
//		i++;
	}
	return  (error);
} */

/* int	run_fill2(char **maze, int dxy[2][8], int x, int y)
{
	static int	error = 0;
	int			i;
	int			nx;
	int			ny;

	if (maze[y][x] == '1' || maze[y][x] == '\0' || maze[y][x] == '\n')
	{
		if (maze[y][x] != '1')
			error++;
		return (0);
	}
	maze[y][x] = '1';
	i = 0;
	while (i < 8)
	{
		nx = x + dxy[0][i];
		ny = y + dxy[1][i];
		if ((!maze[ny][nx] || maze[ny][nx] == '\0' || maze[ny][nx] == '\n') ||
			(maze[ny][nx] != '0' && maze[ny][nx] != '1'))
		{
			error++;
			continue ;
		}
		run_fill2(maze, dxy, nx, ny);
		i++;
	}
	return (error);
} */

/* int run_fill2(char **maze, int dxy[2][8], int startX, int startY) {
    int error = 0;
    int stackX[1000];  // Adjust the size as needed
    int stackY[1000];  // Adjust the size as needed
    int top = -1;

    stackX[++top] = startX;
    stackY[top] = startY;

    while (top >= 0) {
        int x = stackX[top];
        int y = stackY[top--];

        if (maze[y][x] == '1' || maze[y][x] == '\0' || maze[y][x] == '\n') {
            if (maze[y][x] != '1') {
                error++;
            }
            continue;
        }

        maze[y][x] = '1';
int i = 0;
while (i < 8) {
    int nx = x + dxy[0][i];
    int ny = y + dxy[1][i];

    if ((!maze[ny][nx] || maze[ny][nx] == '\0' || maze[ny][nx] == '\n') ||
        (maze[ny][nx] != '0' && maze[ny][nx] != '1')) {
        error++;
    } else {
        stackX[++top] = nx;
        stackY[top] = ny;
    }
    i++; // Increment i to check the next direction
}
    }
    return error;
} */
