/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:21:30 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/12 11:28:30 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy a string to a buffer, ensuring null-termination.
 *
 * @param dest The destination buffer.
 * @param src The source string.
 * @param destsize The size of the destination buffer.
 *
 * @return The length of the source string.
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	offset;

	offset = 0;
	if (destsize > 0)
	{
		while (*(src + offset) != '\0')
		{
			*(dest + offset) = *(src + offset);
			offset++;
			if (offset == destsize)
			{
				offset--;
				break ;
			}
		}
	}
	if (destsize != 0)
		*(dest + offset) = '\0';
	return (ft_strlen(src));
}

// int main(){
// 	char dest[4];
// 	ft_strlcpy(dest, "aaa", 3);
// 	printf("String: '%s'\n", dest);
// }
