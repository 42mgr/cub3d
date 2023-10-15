/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:20:34 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/11 14:22:25 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locate the first occurrence of a character in a memory block.
 *
 * @param s Pointer to the memory block to search.
 * @param c The character to search for.
 * @param n Number of bytes to search in the memory block.
 *
 * @return A pointer to the first occurrence of the character c in the memory 
 * block s, or NULL if the character is not found.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (char)c)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}

// int main(void)
// {
// 	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};
// 	printf("String: '%s'\n", (char *)ft_memchr(tab, -1, 7));
// }
