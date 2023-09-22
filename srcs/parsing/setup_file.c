/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:09:37 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/22 14:45:44 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	write_rgb(int *rgb, int red, int green, int blue)
{
	if ((red > 255 || green > 255 || blue > 255)
		|| (red < 0 || green < 0 || blue < 0))
	{
		ft_putstr_fd("Invalid value for RGB color provided.\n", 1);
		return (1);
	}
	rgb[0] = red;
	rgb[1] = green;
	rgb[2] = blue;
	return (0);
}

int	init_data(t_data *data)
{
	data->mlx = NULL;
	data->start.dir = 0;
	data->start.x = 0;
	data->start.y = 0;
	data->maze = NULL;
	data->textures.n_path = ft_strdup("./textures/default_n_wall");
	data->textures.e_path = ft_strdup("./textures/default_e_wall");
	data->textures.s_path = ft_strdup("./textures/default_s_wall");
	data->textures.w_path = ft_strdup("./textures/default_w_wall");
	write_rgb(data->textures.ceiling_rgb, 0, 0, 255);
	write_rgb(data->textures.floor_rgb, 0, 255, 0);
	data->dim.lines = 0;
	data->dim.llen_head = NULL;
	data->dim.min_x = -1;
	data->dim.min_y = -1;
	data->dim.max_x = -1;
	data->dim.max_y = -1;
	data->fd = -1;
	return (0);
}

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
}

int	check_for_start(t_data *data, char *buffer)
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
			data->start.y = data->dim.lines;
			data->start.x = i;
			if (buffer[i] == 'N')
				data->start.dir = 0;
			else if (buffer[i] == 'E')
				data->start.dir = 90;
			else if (buffer[i] == 'S')
				data->start.dir = 180;
			else if (buffer[i] == 'W')
				data->start.dir = 270;
			buffer[i] = '0';
		}
		i++;
	}
	return (0);
}

char	*read_file(t_data *data, char *path)
{
	int		fd;
	char	*buffer;
	char	*temp;
	char	*line;
	int		len;

	fd = open(path, O_RDONLY);
	buffer = get_next_line(fd);
	while (buffer)
	{
		if (buffer[0] != '\n')
			data->dim.lines++;
		len = ft_strlen(buffer);
		add_length_list(&data->dim.llen_head, data->dim.lines, len);
		check_for_start(data, buffer);
		temp = ft_strjoin(line, buffer);
		free(buffer);
		buffer = get_next_line(fd); //double free siehe unten m;glich?
		line = temp;
	}
	free(buffer);
	close(fd);
	return (line);
}

void	print_ll(t_llen **head)
{
	t_llen	*current;

	current = *head;
	while (current)
	{
		printf("line: %i\tlength: %i\n", current->lno, current->llen);
		current = current->next;
	}
}

int	cont_str_len(char *line, int offset)
{
	int	i;

	i = offset;
	while (!(line[i] == ' ' || line[i] == '\n' || line[i] == '\t')
		|| line[i] == '\0')
		i++;
	return (i);
}

int	parse_path(t_data *data, char *line, int len, int offset)
{
	char	*path;
	char	**color;

	path = (char *)malloc(sizeof(char) * (len + 1));
	path[len] = '\0';
	ft_strlcpy(path, line + offset, len - offset + 1);
	check_file(path);
	color = &data->textures.n_path;
	if (line[0] == 'N')
		color = &data->textures.n_path;
	else if (line[0] == 'S')
		color = &data->textures.s_path;
	else if (line[0] == 'E')
		color = &data->textures.e_path;
	else if (line[0] == 'W')
		color = &data->textures.w_path;
	//color = (char *)malloc(sizeof(char) + (len + 1));
	//color[len] = '\0';
	free(*color);
	*color = path;
	return (0);
}

int	detect_textures(t_data *data, char *line)
{
	int	len;
	int	offset;

	offset = 3;
	if (!ft_strncmp(line, "NO ", offset) || !ft_strncmp(line, "SO ", offset)
		|| !ft_strncmp(line, "WE ", offset)
		|| !ft_strncmp(line, "EA ", offset))
	{
		len = (cont_str_len(line, offset));
		parse_path(data, line, len, offset);
		return (len);
	}
	return (0);
}

int	parse_colors(t_data *data, char *line, int len, int offset)
{
	char	*temp;
	char	**rgb;
	int		*where;

	temp = (char *)malloc(sizeof(char) * (len + offset));
	ft_strlcpy(temp, line + offset, len);
	rgb = ft_split(temp, ',');
	if (line[0] == 'C')
		where = data->textures.ceiling_rgb;
	else
		where = data->textures.floor_rgb;
	if (rgb[0] != 0 && rgb[1] != 0 && rgb[2] != 0)
		write_rgb(where, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	else
		ft_putstr_fd("Invalid RGB color format.\n", 2);
	free(temp);
	free(rgb);
	return (0);
}

int	detect_colors(t_data *data, char *line)
{
	int	len;
	int	offset;

	offset = 2;
	if (!ft_strncmp(line, "C ", offset) || !ft_strncmp(line, "F ", offset))
	{
		len = (cont_str_len(line, offset));
		parse_colors(data, line, len, offset);
		return (len);
	}
	return (0);
}

int	detect_char(char c)
{
	static int	start = 0;

	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (start == 0)
			start++;
		else
			printf("ERROR too many start positions\n");
	}
	else if (!(c == '1' || c == '0' || c == '\n' || c == ' ' || c == 'x'))
		printf("problematic character: %c\n", c);
	return (0);
}

int	read_line(t_data *data, char *line)
{
	char	*line_ptr;

	line_ptr = line;
	while (*line_ptr)
	{
		line_ptr = line_ptr + detect_textures(data, line_ptr);
		line_ptr = line_ptr + detect_colors(data, line_ptr);
		detect_char(*line_ptr);
		line_ptr++;
	}
	return (0);
}

int	setup_file(t_data *data, char **av)
{
	char	*line;
	int		ret;

	ret = init_data(data);
	if (ret == 0)
	{
		line = read_file(data, av[1]);
		read_line(data, line);
		data->maze = ft_split(line, '\n');
	//printf("%s", line);
		free(line);
	}
	if (flood_fill(data) == 0)
		;
	//print_ll(&data->dim.llen_head);
	return (ret);
}
