/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:20:52 by mgraf             #+#    #+#             */
/*   Updated: 2023/06/13 10:03:10 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_set(char c, char *set)
{
	if (c)
	{
		while (*set)
		{
			if (*set == c)
				return (1);
			set++;
		}
	}
	return (0);
}

int	ft_count_parts(char const *s, char c)
{
	int		parts;
	int		i;
	char	*string;

	string = ft_strtrim(s, &c);
	if (!string)
		return (0);
	parts = 0;
	i = 0;
	while (string[i])
	{
		if (ft_is_in_set(string[i], &c) && !(ft_is_in_set(string[i - 1], &c)))
			parts++;
		i++;
	}
	parts++;
	free(string);
	return (parts);
}

void	*ft_clean_up(char **res)
{
	int	i;

	i = 0;
	while (res[i] != NULL)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

void	ft_pop_parts(char **res, char *s, char c, int parts)
{
	int	i;
	int	len;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while ((*s && *s != c) && i < parts)
			{
				len++;
				s++;
			}
			res[i] = ft_substr(s - len, 0, len);
			if (!res[i])
			{
				ft_clean_up(res);
				break ;
			}
			i++;
		}
		else
			s++;
	}
}

/**
 * @brief Splits a string into an array of substrings based on a delimiter
 *  character.
 *
 * @param s The string to split.
 * @param c The delimiter character.
 *
 * @return A pointer to the array of substrings or NULL if allocation fails.
 */
char	**ft_split(char const *s, char c)
{
	char	**res;
	int		parts;

	parts = ft_count_parts(s, c);
	if (ft_strlen(s) == 0)
		parts = 0;
	res = ft_calloc(parts + 1, sizeof(char *));
	if (!res)
		return (NULL);
	ft_pop_parts(res, (char *)s, c, parts);
	return (res);
}
// int	main(void)
// {
// 	char	*string = "      split       this for   me  !       ";
// 	char	delimiter = ' ';
// 	char	**to_free;
// 	to_free = ft_split((char const *)string, (char)delimiter);
// //	write result
// 	int i = 0;
// 	while (to_free[i])
// 	{
// 		printf("String: '%s'\n", to_free[i]);
// 		i++;
// 	}
// 	// free memory
// 	i = 0;
// 	while (to_free[i])
// 	{
// 		free(to_free[i]);
// 		i++;
// 	}
// 	free(to_free);
// }
