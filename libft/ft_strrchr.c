/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 23:35:23 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/18 01:06:52 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrchr(const char *s, int c)
{
	const char	*p;

	p = NULL;
	while (*s)
	{
		if (*s == (char)c)
			p = s;
		s++;
	}
	if (*s == (char)c)
		return ((char*)s);
	return ((char*)p);
}
