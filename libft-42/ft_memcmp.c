/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:20:43 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/05 18:46:33 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compare two memory blocks.
 *
 * @param s1 Pointer to the first memory block.
 * @param s2 Pointer to the second memory block.
 * @param n Number of bytes to compare.
 *
 * @return An integer greater than, equal to, or less than 0, according to the
 *         result of the comparison.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*ptr1;
	char	*ptr2;

	ptr1 = (char *)s1;
	ptr2 = (char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (ptr1[i] == ptr2[i])
			i++;
		else
			break ;
	}
	if (i == n)
		return (0);
	return ((unsigned char)ptr1[i] - (unsigned char)ptr2[i]);
}
