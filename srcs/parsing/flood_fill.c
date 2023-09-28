/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:47:34 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/28 15:47:36 by mgraf            ###   ########.fr       */
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

	copy = (char **)malloc(sizeof(char *) * lines + 1);
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
		ft_putstr_fd("-> Error:\n\tMalloc failed for maze copy\n", 2);
		ret = 1;
	}
	if (ret == 0)
	{
		ret = run_fill(data, dxy, data->start.x, data->start.y);
		if (ret != 0)
			ft_putstr_fd("-> Error:\n\tMaze is not closed\n", 2);
		free_2d_array(data->maze_cpy);
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
