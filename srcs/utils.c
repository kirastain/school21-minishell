/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:45:51 by bbelen            #+#    #+#             */
/*   Updated: 2020/11/18 20:52:37 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_arrlen(char **arr)
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
		free(arr[i++]);
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