/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:20:49 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/10 19:28:00 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
//https://man7.org/linux/man-pages/man3/memcpy.3.html
//https://aticleworld.com/memmove-function-implementation-in-c/
