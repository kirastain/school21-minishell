/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:33:43 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/20 22:26:52 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*s2;
	char			*p;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	s2 = (char*)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	i = 0;
	p = s2;
	while (i < len && *s)
	{
		s2[i] = s[start + i];
		i++;
	}
	s2[i] = '\0';
	return (p);
}
