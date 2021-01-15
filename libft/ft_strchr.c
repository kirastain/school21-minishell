/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 23:30:44 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 18:26:41 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strchr(const char *s, int c)
{
	const char	*p;

	p = NULL;
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
		{
			p = s;
			return ((char*)p);
		}
		s++;
	}
	if (*s == (char)c)
		return ((char*)s);
	return ((char*)p);
}
