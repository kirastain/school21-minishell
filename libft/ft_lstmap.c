/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 02:09:35 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/19 14:01:41 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*first_node;

	if (!lst || !f || !del)
		return (NULL);
	if (!(current = ft_lstnew(f(lst->content))))
		return (NULL);
	first_node = current;
	while (lst)
	{
		if (lst->next)
		{
			current->next = ft_lstnew(f(lst->next->content));
			if (!(current->next))
			{
				ft_lstclear(&first_node, del);
				return (NULL);
			}
			current = current->next;
		}
		lst = lst->next;
	}
	return (first_node);
}
