/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:34:25 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/16 15:17:38 by fheld            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

/**
 * Counts the length of a continous string until a space, tab or newline
*/
int	cont_str_len(char *line, int offset)
{
	int	i;

	i = offset;
	while (!(line[i] == ' ' || line[i] == '\n' || line[i] == '\t')
		|| line[i] == '\0')
		i++;
	return (i);
}

/**
 * Writes the RGB values to the array and checks range 0-255
*/
int	write_rgb(int *rgb, int red, int green, int blue)
{
	if ((red > 255 || green > 255 || blue > 255)
		|| (red < 0 || green < 0 || blue < 0))
	{
		ft_putstr_fd("\e[1;41mError\e[0m\n\tInvalid RGB value provided.\n", 2);
		return (1);
	}
	rgb[0] = red;
	rgb[1] = green;
	rgb[2] = blue;
	return (0);
}

void	replace_nl(char **buffer)
{
	if (*buffer[0] == '\n')
	{
		free(*buffer);
		*buffer = ft_strdup(" \n");
	}
}

/**
 * Initializes the data struct with default values
*/
int	init_data(t_data *data)
{
	data->mlx = NULL;
	data->start.dir = NORTH;
	data->start.x = -1;
	data->start.y = -1;
	data->maze = NULL;
	data->maze_cpy = NULL;
	data->maze_cpy_dim = NULL;
	data->textures.n_path = ft_strdup(DEFAULT_NORTH_TEXTURE);
	data->textures.e_path = ft_strdup(DEFAULT_EAST_TEXTURE);
	data->textures.s_path = ft_strdup(DEFAULT_SOUTH_TEXTURE);
	data->textures.w_path = ft_strdup(DEFAULT_WEST_TEXTURE);
	write_rgb(data->textures.ceiling_rgb, 0, 0, 255);
	write_rgb(data->textures.floor_rgb, 0, 255, 0);
	data->dim.lines = 0;
	data->dim.min_x = -1;
	data->dim.min_y = -1;
	data->dim.max_x = -1;
	data->dim.max_y = -1;
	return (0);
}
