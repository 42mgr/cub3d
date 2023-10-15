/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:21:23 by mgraf             #+#    #+#             */
/*   Updated: 2023/06/13 10:28:17 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef __FreeBSD__
# include <bsd/string.h>
#endif

/**
 * @brief Appends the NUL-terminated string src to the end of dst.
 *
 * @param dst The destination string.
 * @param src The source string.
 * @param size The size of the destination buffer.
 *
 * @return The total length of the string they tried to create. This means 
 * the initial length of dst plus the length of src.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	i;

	dstlen = ft_strlen(dst);
	i = dstlen;
	while (src[i - dstlen] && (i + 1) < size)
	{
		dst[i] = src[i - dstlen];
		i++;
	}
	if (dstlen < size)
		dst[i] = '\0';
	if (size < dstlen)
		return (size + ft_strlen(src));
	else
		return (dstlen + ft_strlen(src));
}
//https://linux.die.net/man/3/strlcat
