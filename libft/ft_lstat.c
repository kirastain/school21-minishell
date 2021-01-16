/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:34:56 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 11:31:54 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstat(t_list *lst, int pos)
{
	int		i;

	i = 0;
	if (pos > ft_lstsize(lst))
		return (NULL);
	if (lst)
	{
		while (i < pos)
		{
			lst = lst->next;
			i++;
		}
		return (lst);
	}
	return (NULL);
}
