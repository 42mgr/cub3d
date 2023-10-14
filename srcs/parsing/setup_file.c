/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:09:37 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 16:37:45 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
t_llen	*create_length_node(int line, int length)
{
	t_llen	*node;

	node = (t_llen *)malloc(sizeof(t_llen));
	node->llen = length;
	node->lno = line;
	node->next = NULL;
	return (node);
}

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
} */

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
		ft_putstr_fd("\e[1;41mError\e[0m\n\tInvalid RGB color format.\n", 2);
		return (err);
	}
	free(temp);
	free_2d_array(rgb);
	return (err);
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
