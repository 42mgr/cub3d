/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:47:34 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/22 14:58:13 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_maze(char **maze, int lines)
{
	int	x;
	int	y;

	y = 0;
	while (y < lines)
	{
		x = 0;
		while (maze[y][x])
		{
			printf("%c", maze[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

char	**duplicate_maze(int lines, char **maze)
{
	char	**copy;
	int		x;
	int		len;

	copy = (char **)malloc(sizeof(char *) * lines);
	x = 0;
	len = 0;
	(void)len;
	while (maze[x])
	{
		len = ft_strlen(maze[x]);
		copy[x] = ft_strdup(maze[x]);
		x++;
	}
	return (copy);
}
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
			return (0);
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

int	flood_fill(t_data *data)
{
	int		errors;
	int		dxy[2][8];

	create_dxy(dxy);
	errors = 0;
	data->maze_cpy = duplicate_maze(data->dim.lines, data->maze);
	errors = run_fill(data, dxy, data->start.x, data->start.y - 1);
	//printf("min_x: %i, max_x: %i, min_y: %i, max_y: %i\n", data->dim.min_x, data->dim.max_x, data->dim.min_y, data->dim.max_y);
	printf("---> error: %i\n", errors);
	//free (maze_cpy); // and while loop ...
	return (0);
}
