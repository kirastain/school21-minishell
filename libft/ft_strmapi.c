/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:22:52 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/12 16:33:07 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	char	*res;
	int		i;

	if (!f || !s)
		return (NULL);
	p = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!p)
		return (NULL);
	res = p;
	i = 0;
	while (*s)
	{
		*p = f(i, *s);
		p++;
		i++;
		s++;
	}
	*p = '\0';
	return (res);
}
