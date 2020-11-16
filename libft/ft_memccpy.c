/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 21:24:03 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/17 18:19:49 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dest, void *src, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	*s;

	p = (unsigned char*)dest;
	s = (unsigned char*)src;
	while (n)
	{
		*p = *s;
		p++;
		if (*s == (unsigned char)c)
			return ((void*)p);
		s++;
		n--;
	}
	return (NULL);
}
