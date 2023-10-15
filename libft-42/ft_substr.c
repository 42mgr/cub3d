/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:17 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/12 18:55:54 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_count_len(char const *s, unsigned int start, size_t len)
{
	size_t	ls;

	ls = 0;
	ls = ft_strlen(s);
	if (len > ls)
		len = ls;
	if (start > ls)
		len = 0;
	if (start == ls - 1 && len)
		len = 1;
	return (len);
}

/**
 * @brief Allocates and returns a substring from the string 's'.
 *
 * The substring begins at index 'start' and has a maximum length of 'len'.
 *
 * @param s The string to create the substring from.
 * @param start The starting index of the substring in 's'.
 * @param len The maximum length of the substring.
 *
 * @return The substring. NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*returnstr;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_count_len(s, start, len);
	returnstr = (char *)malloc((len + 1) * sizeof(*s));
	if (returnstr == NULL)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (s[start] && i < len)
		{
			returnstr[i] = s[start + i];
			i++;
		}
	}
	returnstr[i] = '\0';
	return (returnstr);
}
