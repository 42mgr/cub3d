/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:41:29 by mgraf             #+#    #+#             */
/*   Updated: 2022/11/30 16:07:05 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the length of a null-terminated string.
 *
 * @param str The string to calculate the length of.
 *
 * @return The length of the string.
 */
size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length] != '\0')
		length++;
	return (length);
}

/* int main(void)
{
	char *string = "ABC";
	ft_strlen(string);
	//printf("%i", ft_strlen(string));

	return 0;
} */
