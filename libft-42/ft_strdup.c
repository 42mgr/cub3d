/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:35:54 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/11 17:23:42 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Duplicate a string.
 *
 * @param s The string to duplicate.
 *
 * @return The duplicated string, or NULL if the allocation fails.
 */
char	*ft_strdup(const char *s)
{
	int		length;
	char	*ptr;
	int		i;

	length = ft_strlen(s);
	ptr = malloc(length + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i <= length)
	{
		if (i == length)
		{
			ptr[length] = '\0';
			break ;
		}
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}
