/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:45:51 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 21:44:36 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_in(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int		ft_arrlen(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	ft_array_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_array_realloc(char **src, char *line)
{
	char	**arr;
	int		i;

	i = 0;
	arr = (char **)malloc(sizeof(char *) * (ft_arrlen(src) + 2));
	while (src[i] != NULL)
	{
		arr[i] = ft_strdup(src[i]);
		i++;
	}
	arr[i++] = ft_strdup(line);
	arr[i] = NULL;
	i = 0;
	ft_array_free(src);
	return (arr);
}
