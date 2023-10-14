/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_detect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:31:54 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 16:33:38 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks for 'C ' or 'F ' and then tries to parse the colors
*/
int	detect_colors(t_data *data, char *line, int *error)
{
	int	len;
	int	offset;

	offset = 2;
	if (!ft_strncmp(line, "C ", offset) || !ft_strncmp(line, "F ", offset))
	{
		len = (cont_str_len(line, offset));
		if (parse_colors(data, line, len, offset))
			*error = 1;
		return (len);
	}
	return (0);
}

/**
 * Checks for invalid characters in the map and multiple starting positions
*/
int	detect_char(char c)
{
	static int	start = 0;

	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (start == 0)
			start++;
		else
		{
			ft_putstr_fd("\e[1;41mError\e[0m\n\tMultiple starting positions.\n", 2);
			return (1);
		}
	}
	else if (!(c == '1' || c == '0' || c == '\n' || c == ' ' || c == 'x'))
	{
		ft_putstr_fd("\e[1;41mError\e[0m\n\tInvalid character in map: ", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	return (0);
}

/**
 * Checks for 'NO ', 'SO ', 'WE ' or 'EA ' and then tries to parse the path
*/
int	detect_textures(t_data *data, char *line, int *error)
{
	int	len;
	int	offset;

	offset = 3;
	if (!ft_strncmp(line, "NO ", offset) || !ft_strncmp(line, "SO ", offset)
		|| !ft_strncmp(line, "WE ", offset)
		|| !ft_strncmp(line, "EA ", offset))
	{
		len = (cont_str_len(line, offset));
		if (parse_path(data, line, len, offset))
			*error = 1;
		return (len);
	}
	return (0);
}

/**
 * Identifies a (valid) starting position and direction of the player
 * and sets it to '0'
*/
int	check_for_start(t_data *data, char *buffer, int line)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if ((buffer[i] == 'N' || buffer[i] == 'S' || buffer[i] == 'E'
				|| buffer[i] == 'W') && (buffer[i + 1] == '1'
				|| buffer[i + 1] == '0') && (buffer[i - 1] == '1'
				|| buffer[i - 1] == '0'))
		{
			data->start.y = line;
			data->start.x = i;
			if (buffer[i] == 'N')
				data->start.dir = NORTH;
			else if (buffer[i] == 'E')
				data->start.dir = EAST;
			else if (buffer[i] == 'S')
				data->start.dir = SOUTH;
			else if (buffer[i] == 'W')
				data->start.dir = WEST;
			buffer[i] = '0';
		}
		i++;
	}
	return (0);
}
