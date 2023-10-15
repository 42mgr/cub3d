/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:39:50 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/12 19:00:24 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_i_len(int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_i_special(void)
{
	char	*s;

	s = ft_calloc(12, sizeof(char));
	if (!s)
		return (NULL);
	ft_memcpy(s, "-2147483648", 11);
	return (s);
}

/**
 * @brief Converts an integer to a string.
 *
 * This function converts the integer passed as argument to a string 
 * representation.
 *
 * @param n The integer to be converted.
 *
 * @return The string representation of the integer passed as argument.
 *         NULL if the allocation fails.
 */
char	*ft_itoa(int n)
{
	char	*s;
	int		len;

	len = ft_i_len(n);
	if (n == -2147483648)
		return (ft_i_special());
	if (n < 0 || n == 0)
		len++;
	s = ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		s[0] = '-';
	}
	while (n / 10 != 0)
	{
		s[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	s[len - 1] = n + '0';
	return (s);
}

// int	main(void)
// {
// 	int	n;
// 	char *s;

// 	n = -88;
// 	s = ft_itoa(n);
// 	printf("String is: '%s'\n", s);
// 	free(s);
// }
