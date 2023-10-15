/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:20:56 by mgraf             #+#    #+#             */
/*   Updated: 2023/06/13 10:04:02 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

/**
 * @brief Copies n bytes from memory area src to memory area dest.
 *
 * @param dest Pointer to the destination array where the content is to be 
 * copied.
 * @param src Pointer to the source of data to be copied.
 * @param n Number of bytes to copy.
 *
 * @return A pointer to the destination array, which is dest.
 */
void	*ft_memmove(void *dest, void *src, size_t n)
{
	char	*s;
	char	*d;

	s = (char *)src;
	d = (char *)dest;
	if (s == NULL && d == NULL)
		return (NULL);
	if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}
//https://man7.org/linux/man-pages/man3/memmove.3.html
