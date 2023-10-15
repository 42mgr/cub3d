/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:34:43 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/14 17:45:59 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Deletes and frees the memory of all elements in a linked list.
 *
 * @param lst A pointer to the first element of the linked list.
 * @param del The function used to delete the content of each element.
 *            This function is called on each element before it is freed.
 *            If NULL, the content will not be freed.
 *
 * @note If the linked list is NULL or the del function is NULL, the function
 *  does nothing.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del || !*lst)
		return ;
	while (lst && *lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}
