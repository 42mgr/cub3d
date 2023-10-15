/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:22:22 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/05 16:44:05 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Converts a lowercase letter to its corresponding uppercase letter.
 *
 * @param c The character to be converted.
 * @return The uppercase equivalent of the input character, or the input 
 * character if it is not a lowercase letter.
 *
 * @note This function assumes that the input character is an ASCII character.
 */
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
