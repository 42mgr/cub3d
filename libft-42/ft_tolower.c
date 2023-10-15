/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:22:10 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/05 16:45:53 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @file ft_tolower.c
 * @brief Converts an uppercase letter to its lowercase equivalent.
 *
 * The ft_tolower() function converts an uppercase letter to its lowercase
 * equivalent. If the argument is already a lowercase letter or is not an
 * alphabetic character, the argument is returned unchanged.
 *
 * @param c The character to be converted.
 * @return The lowercase equivalent of the input character, if it is an
 * uppercase letter. Otherwise, the input character is returned unchanged.
 */
int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}
