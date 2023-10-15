/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:51:34 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/10 19:02:26 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Applies the function 'f' to each character of the string 's' to create a new
 * string resulting from successive applications of 'f'.
 *
 * @param s The string to iterate over.
 * @param f The function to apply to each character of 's'.
 *
 * @return The new string created from the successive applications of 'f', or
 * NULL if the allocation fails.
 *
 * @example
 * char *str = "hello";
 * char *new_str = ft_strmapi(str, &add_one);
 * // new_str is now "ifmmp"
 *
 * static char add_one(unsigned int i, char c)
 * {
 *     return c + 1;
 * }
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*buffer;

	if (s == NULL || !f)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (buffer == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		buffer[i] = f(i, s[i]);
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}
