/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 23:30:44 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/18 00:59:47 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strchr(const char *s, int c)
{
	const char	*p;

	p = NULL;
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
