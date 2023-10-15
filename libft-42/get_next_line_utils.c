/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:38:37 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/20 22:54:02 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	found_newline(t_lgnl *stash)
{
	int		i;
	t_lgnl	*current;

	if (stash == NULL)
		return (0);
	current = ft_lst_get_last(stash);
	i = 0;
	while (current->cont[i])
	{
		if (current->cont[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_lgnl	*ft_lst_get_last(t_lgnl *stash)
{
	t_lgnl	*current;

	current = stash;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	generate_line(char **line, t_lgnl *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->cont[i])
		{
			if (stash->cont[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_stash(t_lgnl *stash, int isEmpty)
{
	t_lgnl	*current;
	t_lgnl	*next;

	if (isEmpty == 1)
	{
		free(stash->cont);
		free(stash);
		return ;
	}
	current = stash;
	while (current)
	{
		free(current->cont);
		next = current->next;
		free(current);
		current = next;
	}
}

/* int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
} */
