/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:33:40 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 23:58:59 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var(char *arg, char **env)
{
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	while (env[i])
	{
		if (ft_strcmp(arg, env[i]) == 0)
		{
			value = ft_strdup(env[i + 1]);
			return (value);
		}
		i++;
	}
	return (NULL);
}

int		if_internal(char *name)
{
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	if (ft_strcmp(name, "exit") == 0)
		return (1);
	if (ft_strcmp(name, "export") == 0)
		return (1);
	if (ft_strcmp(name, "pwd") == 0)
		return (1);
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	return (0);
}

int		create_command(char **tokens, t_struct *conf)
{
	t_command	*com;
	int			flag_name;
	char		*arg;
	int			i;

	arg = NULL;
	flag_name = 0;
	i = 0;
	if (!(com = init_command(conf)))
		error_quit("Memory issue", conf);
	while (tokens[i])
	{
		if (flag_name == 0)
		{
			if (!(if_internal(tokens[i])) && !(if_command_name(tokens[i],
					get_env_var("PATH", conf->env))))
				error_code(tokens[i], -5, conf);
			com->name = ft_strdup(tokens[i]);
			flag_name = 1;
		}
		else if (ft_strcmp(tokens[i], ">") == 0 ||
			ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">>") == 0)
		{
			com->arrows = ft_array_realloc(com->arrows, tokens[i]);
			i++;
			com->file = ft_array_realloc(com->file, tokens[i]);
		}
		else if (ft_strcmp(tokens[i], "|") == 0 ||
			ft_strcmp(tokens[i], ";") == 0)
		{
			com->pipe_sc = tokens[i][0];
			i++;
			break ;
		}
		else
		{
			arg = tokens[i];
			if (!(arg = edit_arg(arg, conf)))
				error_quit("Invalid argument", conf);
			com->args = ft_array_realloc(com->args, arg);
		}
		i++;
	}
	ft_comadd_back(&(conf->command), com);
	return (i);
}

void	analyze_tokens(t_struct *conf, char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ":") == 0 || ft_strcmp(tokens[i], "|") == 0)
		{
			conf->betweens = ft_array_realloc(conf->betweens, tokens[i]);
			i++;
		}
		else
		{
			i = i + create_command(&tokens[i], conf);
		}
	}
}
