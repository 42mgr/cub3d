/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:09:37 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/28 22:18:35 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Writes the RGB values to the array and checks range 0-255
*/
int	write_rgb(int *rgb, int red, int green, int blue)
{
	if ((red > 255 || green > 255 || blue > 255)
		|| (red < 0 || green < 0 || blue < 0))
	{
		ft_putstr_fd("-> Error:\n\tInvalid value for RGB color provided.\n", 2);
		return (1);
	}
	rgb[0] = red;
	rgb[1] = green;
	rgb[2] = blue;
	return (0);
}

/**
 * Initializes the data struct with default values
 * !!! fd not necessary? llen_head not necessary?
*/
int	init_data(t_data *data)
{
	data->mlx = NULL;
	data->start.dir = NORTH;
	data->start.x = -1;
	data->start.y = -1;
	data->maze = NULL;
	data->maze_cpy = NULL;
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

/**
 * Returns an intialised node for the linked list
*/
t_llen	*create_length_node(int line, int length)
{
	t_llen	*node;

	node = (t_llen *)malloc(sizeof(t_llen));
	node->llen = length;
	node->lno = line;
	node->next = NULL;
	return (node);
}

/**
 * Adds a node to the end of linked list
*/
void	add_length_list(t_llen **head, int line, int length)
{
	t_llen	*current;

	if (*head == NULL)
		*head = create_length_node(line, length);
	else
	{
		current = *head;
		while (current != NULL && current->next != NULL)
			current = current->next;
		current->next = create_length_node(line, length);
	}
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

void	replace_nl(char **buffer)
{
	if (*buffer[0] == '\n')
	{
		free(*buffer);
		*buffer = ft_strdup(" \n");
	}
}

/**
 * Reads the file and saves the lines in a char *line
 * !!! linked list not necessary??
*/
char	*read_file(t_data *data, char *path)
{
	int		fd;
	char	*buffer;
	char	*temp;
	char	*line;
	int		i;

	fd = open(path, O_RDONLY);
	buffer = get_next_line(fd);
	i = 0;
	line = ft_strdup("");
	while (buffer)
	{
		data->dim.lines++;
		replace_nl(&buffer);
		check_for_start(data, buffer, i);
		temp = ft_strjoin_mod(line, buffer);
		buffer = get_next_line(fd);
		line = temp;
		i++;
	}
	if (buffer)
		free(buffer);
	close(fd);
	return (line);
}

/**
 * Helper function to print the linked list
*/
/*
void	print_ll(t_llen **head)
{
	t_llen	*current;

	current = *head;
	while (current)
	{
		printf("line: %i\tlength: %i\n", current->lno, current->llen);
		current = current->next;
	}
} */

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
 * Copies the color path to the data struct and checks if the file exists
*/
int	parse_path(t_data *data, char *line, int len, int offset)
{
	char	*path;
	char	**color;
	int		ret;

	ret = 1;
	path = (char *)malloc(sizeof(char) * (len + 1));
	if (!path)
		return (ret);
	path[len] = '\0';
	ft_strlcpy(path, line + offset, len - offset + 1);
	ret = check_file(path);
	color = &data->textures.n_path;
	if (line[0] == 'N')
		color = &data->textures.n_path;
	else if (line[0] == 'S')
		color = &data->textures.s_path;
	else if (line[0] == 'E')
		color = &data->textures.e_path;
	else if (line[0] == 'W')
		color = &data->textures.w_path;
	free(*color);
	*color = path;
	return (ret);
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
 * Takes the line with the identified color and parses it to the data struct
*/
int	parse_colors(t_data *data, char *line, int len, int offset)
{
	char	*temp;
	char	**rgb;
	int		*loc;
	int		err;

	err = 1;
	temp = (char *)malloc(sizeof(char) * (len + offset));
	if (!temp)
		return (err);
	ft_strlcpy(temp, line + offset, len);
	rgb = ft_split(temp, ',');
	if (line[0] == 'C')
		loc = data->textures.ceiling_rgb;
	else
		loc = data->textures.floor_rgb;
	if (rgb[0] != 0 && rgb[1] != 0 && rgb[2] != 0)
		err = write_rgb(loc, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	else
	{
		ft_putstr_fd("->Error:\n\tInvalid RGB color format.\n", 2);
		return (err);
	}
	free(temp);
	free_2d_array(rgb);
	return (err);
}

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
			ft_putstr_fd("-> Error:\n\tMultiple starting positions.\n", 2);
			return (1);
		}
	}
	else if (!(c == '1' || c == '0' || c == '\n' || c == ' ' || c == 'x'))
	{
		ft_putstr_fd("-> Error:\n\tInvalid character in map: ", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	return (0);
}

/**
 * Reads the line and checks for valid textures, colors and characters
*/
int	read_line(t_data *data, char *line)
{
	char	*line_ptr;
	int		error;

	line_ptr = line;
	error = 0;
	while (*line_ptr)
	{
		line_ptr = line_ptr + detect_textures(data, line_ptr, &error);
		line_ptr = line_ptr + detect_colors(data, line_ptr, &error);
		if (detect_char(*line_ptr))
			error = 1;
		if (error != 0)
		{
			free(line);
			return (error);
		}
		line_ptr++;
	}
	return (error);
}

/**
 * Main to intialize the data struct and read the file and check validity
*/
int	setup_file(t_data *data, char **av)
{
	char	*line;
	int		ret;

	ret = init_data(data);
	if (ret == 0)
	{
		line = read_file(data, av[1]);
		ret = read_line(data, line);
	}
	if (ret == 0)
	{
		data->maze = ft_split(line, '\n');
		if (!data->maze)
			ret = 1;
		free(line);
	}
	if (ret == 0)
		ret = flood_fill(data);
	return (ret);
}
