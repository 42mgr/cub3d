/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:51:42 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/14 17:00:43 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Returns the last element of a linked list.
 *
 * @param lst The linked list.
 * @return The last element of the linked list.
 */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp != NULL)
	{
		if (temp->next == NULL)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}
