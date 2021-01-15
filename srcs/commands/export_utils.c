/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:50:05 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 15:41:33 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int			check_arg_env(char **env, char *value)
{
	int		i;
	char	*tmp;

	i = 0;
	while (value[i] != '=')
		i++;
	value[i] = '\0';
	tmp = ft_strdup(value);
	value[i] = '=';
	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], tmp) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

char		**change_exist_arg(char **env, char *value)
{
	int		i;
	char	*name;
	char	*new_value;

	i = 0;
	while (value[i] != '=')
		i++;
	value[i] = '\0';
	name = ft_strdup(value);
	new_value = ft_strdup(&value[++i]);
	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], name) == 0)
		{
			free(env[++i]);
			env[i] = NULL;
			env[i] = ft_strdup(new_value);
			break ;
		}
		i++;
	}
	free(name);
	free(new_value);
	return (env);
}

char		**add_arg_new(char **env, char *value)
{
	int		i;
	char	*name;
	char	*new_value;

	i = 0;
	while (value[i] != '=')
		i++;
	value[i] = '\0';
	name = ft_strdup(value);
	i++;
	new_value = ft_strdup(&value[i]);
	env = ft_array_realloc(env, name);
	env = ft_array_realloc(env, new_value);
	free(name);
	free(new_value);
	return (env);
}
