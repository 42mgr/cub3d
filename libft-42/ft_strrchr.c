/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:45:33 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/12 18:32:05 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_strrchr.c
 * @brief The ft_strrchr() function locates the last occurrence of c (converted 
 * to a char) in the string pointed to by s. The terminating null character is 
 * considered to be part of the string; therefore if c is `\0', the functions 
 * locate the terminating `\0'.
 *
 * @param str The string to be searched.
 * @param c The character to be located.
 * @return A pointer to the located character, or NULL if the character does 
 * not appear in the string.
 */
char	*ft_strrchr(const char *str, int c)
{
	size_t	i;

	i = ft_strlen(str);
	while (str[i] != (unsigned char)c)
	{
		if (i == 0)
			return (NULL);
		i--;
	}
	if (i <= ft_strlen(str))
		return ((char *)&str[i]);
	return (NULL);
}
// int main(){
// 	char str[] = "bonjour";
// 	printf("String: '%s'\n", ft_strrchr(str, 's'));
// }
