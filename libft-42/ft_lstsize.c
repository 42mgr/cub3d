/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:33:57 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/14 16:49:47 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of elements in a linked list.
 *
 * @param lst A pointer to the first element of the list.
 *
 * @return The number of elements in the list.
 */
int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*temp;

	temp = lst;
	size = 0;
	while (temp != NULL)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}
