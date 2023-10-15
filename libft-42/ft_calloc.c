/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:18:26 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/16 13:53:42 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates memory for an array of num elements of size bytes each and 
 * returns a pointer to the allocated memory.
 *
 * @param num The number of elements to allocate memory for.
 * @param size The size of each element.
 *
 * @return A pointer to the allocated memory.
 * @return NULL if the allocation fails.
 */
void	*ft_calloc( size_t num, size_t size )
{
	char	*ptr;

	ptr = malloc(num * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, num * size);
	return (ptr);
}
