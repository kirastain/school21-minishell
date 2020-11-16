/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 00:27:12 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/08 01:07:28 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	s = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	p = s;
	while (*s1 != '\0')
		*s++ = *s1++;
	while (*s2 != '\0')
		*s++ = *s2++;
	*s = '\0';
	return (p);
}
