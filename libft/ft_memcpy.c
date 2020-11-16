/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 23:53:46 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/17 18:13:46 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*s;

	if (dest == src)
		return (dest);
	i = 0;
	p = dest;
	s = src;
	while (i < n)
	{
		*p = *s;
		i++;
		s++;
		p++;
	}
	return (dest);
}
