/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:37:39 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/20 22:54:13 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static t_lgnl	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (int)read(fd, &line, 0) < 0)
	{
		if (stash != NULL)
		{
			free_stash(stash, 1);
			stash = NULL;
		}
		return (NULL);
	}
	read_and_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash, 0);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_stash(int fd, t_lgnl **stash)
{
	char	*buf;
	int		readed;

	readed = 1;
	while (!found_newline(*stash) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		readed = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && readed == 0) || readed <= 0)
		{
			free(buf);
			return ;
		}
		buf[readed] = '\0';
		add_to_stash(stash, buf, readed);
		free(buf);
	}
}

void	add_to_stash(t_lgnl **stash, char *buf, int readed)
{
	int		i;
	t_lgnl	*last;
	t_lgnl	*new_node;

	new_node = malloc(sizeof(t_lgnl));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->cont = malloc(sizeof(char) * (readed + 1));
	if (new_node->cont == NULL)
		return ;
	i = 0;
	while (buf[i] && i < readed)
	{
		new_node->cont[i] = buf[i];
		i++;
	}
	new_node->cont[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*stash);
	last->next = new_node;
}

void	extract_line(t_lgnl *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->cont[i])
		{
			if (stash->cont[i] == '\n')
			{
				(*line)[j++] = stash->cont[i];
				break ;
			}
			(*line)[j++] = stash->cont[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_lgnl **stash)
{
	t_lgnl	*last;
	t_lgnl	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_lgnl));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->cont[i] && last->cont[i] != '\n')
		i++;
	if (last->cont && last->cont[i] == '\n')
		i++;
	clean_node->cont = malloc(sizeof(char) * ((ft_strlen(last->cont) - i) + 1));
	if (clean_node->cont == NULL)
		return ;
	j = 0;
	while (last->cont[i])
		clean_node->cont[j++] = last->cont[i++];
	clean_node->cont[j] = '\0';
	free_stash(*stash, 0);
	*stash = clean_node;
}

/* int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	int		i;
	int		lnumber;

	fd = open("test_text", O_RDONLY);
	if (argc != 2)
		lnumber = 1;
	else
		lnumber = atoi(argv[1]);
	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (i == lnumber)
			printf("Line %i: %s", i, line);
		if (line == NULL)
			break ;
		free(line);
		i++;
	}
	return (0);
} */
