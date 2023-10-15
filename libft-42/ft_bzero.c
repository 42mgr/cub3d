/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:42:57 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/16 12:06:53 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Sets the first @p len bytes of the memory area pointed to by @p s
 *  to zero.
 *
 * @param s Pointer to the memory area to be zeroed.
 * @param len Number of bytes to be zeroed.
 */
void	ft_bzero(void *s, size_t len)
{
	char	*ptr;

	ptr = (char *)s;
	while (len--)
	{
		ptr[len] = '\0';
	}
}

//https://man7.org/linux/man-pages/man3/bzero.3.html
