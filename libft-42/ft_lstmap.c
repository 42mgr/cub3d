/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:59:29 by mgraf             #+#    #+#             */
/*   Updated: 2022/12/16 11:52:47 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Applies the function 'f' to each element of the linked list 'lst' and creates
 * a new list with the results. The 'del' function is used to delete the content
 * of an element if needed. If the allocation of a new element fails, the 'del'
 * function is used to delete the content of all the elements created so far and
 * the function returns NULL.
 *
 * @param lst The linked list to iterate over.
 * @param f The function to apply to each element.
 * @param del The function to delete the content of an element if needed. For
 * example, if the linked list contains dynamically allocated memory that needs
 * to be freed, the 'del' function should be implemented to free that memory.
 * @return The new list with the results of the 'f' function applied to each
 * element, or NULL if the allocation of a new element fails.
 *
 * @code
 * void *my_del(void *content)
 * {
 *     free(content);
 * }
 *
 * t_list *my_lstmap = ft_lstmap(lst, my_function, my_del);
 * @endcode
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*new;

	ret = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&ret, (del));
		}
		ft_lstadd_back(&ret, new);
		lst = lst->next;
	}
	return (ret);
}
