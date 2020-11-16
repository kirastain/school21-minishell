/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 23:25:58 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/19 15:02:40 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_strlcat(char *dest, char *src, size_t size)
{
	size_t			i;
	size_t			end;

	i = ft_strlen(dest);
	end = i;
	if (!(*src))
		return (i);
	if (size <= i)
		return (size + ft_strlen(src));
	while (*src)
	{
		if (i + 1 < size)
		{
			dest[i] = *src;
			end++;
		}
		src++;
		i++;
	}
	dest[end] = '\0';
	return (i);
}
