/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:44:47 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/17 17:42:51 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s)
{
	char	*d;
	char	*p;

	d = (char*)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!d)
		return (NULL);
	p = d;
	while ((*d++ = *s++))
		;
	*d = '\0';
	return (p);
}
