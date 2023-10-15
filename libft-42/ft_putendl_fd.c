/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:06:06 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/11 13:15:44 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Outputs the string 's' to the given file descriptor 'fd', followed by a 
 * newline character.
 *
 * @param s The string to output.
 * @param fd The file descriptor on which to write the string.
 *
 * @return void
 */
void	ft_putendl_fd(char *s, int fd)
{
	char	n;

	if (fd != -1 && (s != NULL))
	{
		n = '\n';
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
		write(fd, &n, 1);
	}
}
