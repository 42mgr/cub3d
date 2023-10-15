/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 12:18:34 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/11 13:04:44 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs a character to the specified file descriptor.
 *
 * @param c The character to output.
 * @param fd The file descriptor to output to.
 *
 * @return void
 */
void	ft_putchar_fd(char c, int fd)
{
	if (fd != -1 && ft_isascii(c))
		write(fd, &c, 1);
}
