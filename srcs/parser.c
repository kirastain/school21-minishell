/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:42:19 by bbelen            #+#    #+#             */
/*   Updated: 2020/11/22 18:34:24 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		**parser_env(char **env)
{
	char	**env_own;
	int		i;
	int		j;
	char	*tmp;

	if (!(env_own = (char **)malloc(sizeof(char*) * (ft_arrlen(env) + 1))))
		exit(1);
	env_own[0] = NULL;
	i = 0;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		env[i][j] = '\0';
		tmp = ft_strdup(env[i]);
		env_own = ft_array_realloc(env_own, tmp);
		free(tmp);
		tmp = ft_strdup(&env[i][++j]);
		env_own = ft_array_realloc(env_own, tmp);
		free(tmp);
	}
	return (env_own);
}