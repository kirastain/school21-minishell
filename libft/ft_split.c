/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 23:24:49 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/22 15:53:17 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	speclen(const char *str, char sep)
{
	int			i;

	i = 0;
	while (*str != sep && *str)
	{
		i++;
		str++;
	}
	return (i);
}

static char		*ft_memcpyend(char *dst, const char *src, char sep)
{
	ft_memcpy((void*)dst, (void*)src, speclen(src, sep));
	*(dst + speclen(src, sep)) = 0;
	return (dst);
}

static int		num_c(char *s, char c)
{
	int			len;
	int			word;
	int			sym;

	len = 0;
	word = 0;
	sym = 1;
	while (*s)
	{
		if (*s != c && sym)
		{
			word = 1;
			sym = 0;
			len++;
		}
		if (*s == c && word)
		{
			word = 0;
			sym = 1;
		}
		s++;
	}
	return (len);
}

static char		**free_all(char **arr, int len)
{
	len--;
	while (len >= 0)
	{
		free(arr[len]);
		len--;
	}
	free(arr);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char		**tmp;
	int			i;
	int			flag;

	if (!s)
		return (NULL);
	flag = 1;
	i = 0;
	if (!(tmp = (char**)malloc(sizeof(char*) * (num_c((char*)s, c) + 1))))
		return (NULL);
	tmp[num_c((char*)s, c)] = 0;
	while (*s)
	{
		if (flag && *s != c)
		{
			if (!(tmp[i] = (char*)malloc(sizeof(char) * (speclen(s, c) + 1))))
				return (free_all(tmp, i + 1));
			ft_memcpyend(tmp[i++], s, c);
		}
		flag = 0;
		if (*s == c)
			flag = 1;
		s++;
	}
	return (tmp);
}
