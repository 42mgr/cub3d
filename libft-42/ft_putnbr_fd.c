/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:16:57 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/11 13:49:10 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Outputs the integer 'n' to the given file descriptor 'fd'.
 *
 * @param n The integer to output.
 * @param fd The file descriptor on which to write.
 *
 * @return void
 */
void	ft_putnbr_fd(int n, int fd)
{
	if (fd != -1)
	{
		if (n == -2147483648)
			ft_putstr_fd("-2147483648", fd);
		else
		{
			if (n < 0)
			{
				ft_putchar_fd('-', fd);
				n = -n;
			}
			if (n > 9)
				ft_putnbr_fd((n / 10), fd);
			ft_putchar_fd(((n % 10) + '0'), fd);
		}
	}
}
