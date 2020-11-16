/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:26:45 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/16 20:26:17 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void						*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	const unsigned char		*src;

	i = 0;
	src = s;
	while (i < n)
	{
		if (*src == (unsigned char)c)
			return ((void *)src);
		i++;
		src++;
	}
	return (NULL);
}
