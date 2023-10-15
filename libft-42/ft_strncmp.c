/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:21:47 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/12 18:36:09 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compare two strings up to a given number of characters.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n The maximum number of characters to compare.
 *
 * @return An integer greater than, equal to, or less than 0, according to
 *  whether the string s1 is greater than, equal to, or less than the string 
 * s2 when comparing their first n characters. The comparison is done using 
 * unsigned characters, so that '\200' is greater than '\0'.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
		{
			if (i - n == 0)
				break ;
			i++;
		}
		else
			break ;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
