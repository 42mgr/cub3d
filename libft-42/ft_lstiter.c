/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:48:27 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/14 17:57:36 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Applies the function `f` to each element of the linked list `lst`.
 *
 * @param lst The linked list to iterate over.
 * @param f The function to apply to each element of the linked list.
 *          The function must take a void pointer as its parameter.
 *          The value pointed to by the void pointer is the content of the
 *          current element of the linked list.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
