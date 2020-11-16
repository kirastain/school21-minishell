/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 23:35:50 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/11 23:19:42 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	len;

	if (!(*to_find))
		return ((char*)str);
	len = ft_strlen(to_find);
	while (*str && n >= len)
	{
		n--;
		if (!ft_memcmp(str, to_find, len))
			return ((char*)str);
		str++;
	}
	return (NULL);
}
