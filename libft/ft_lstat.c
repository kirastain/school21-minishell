/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen@student.21-school.ru <bbelen>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:42:20 by bbelen@stud       #+#    #+#             */
/*   Updated: 2020/09/21 13:05:46 by bbelen@stud      ###   ########.fr       */
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
