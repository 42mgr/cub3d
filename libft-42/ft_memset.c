/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:07:06 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/01 15:42:20 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fill a byte string with a byte value.
 *
 * @param str Pointer to the byte string to be filled.
 * @param c The byte value to be set.
 * @param len Number of bytes to be set to the value.
 * @return A pointer to the memory area str.
 */
void	*ft_memset(void *str, int c, unsigned int len)
{
	unsigned int	i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)str;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

// size_t https://man7.org/linux/man-pages/man7/system_data_types.7.html