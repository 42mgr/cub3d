/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:35:23 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/11 13:39:08 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Outputs the string 's' to the file descriptor 'fd'.
 *
 * @param s The string to output.
 * @param fd The file descriptor to output to.
 *
 * @return None.
 */
void	ft_putstr_fd(char *s, int fd)
{
	if (fd != -1 && s != NULL)
	{
		while (*s)
		{
			ft_putchar_fd(*s, fd);
			s++;
		}
	}
}
