/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:33:40 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 22:23:32 by bbelen           ###   ########.fr       */
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
	//printf("tokens len is %d with first as %s\n", ft_arrlen(tokens), tokens[i]);
	while (tokens[i])
	{
		if (flag_name == 0)
		{
			if (!(if_internal(tokens[i])) && !(if_command_name(tokens[i], get_env_var("PATH", conf->env))))
				error_code(tokens[i], -5, conf);
			com->name = ft_strdup(tokens[i]);
			flag_name = 1;
			//printf("com name is %s\n", com->name);
		}
		else if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], "<") == 0 ||
					ft_strcmp(tokens[i], ">>") == 0)
		{
			//printf("arrow found\n");
			com->arrows = ft_array_realloc(com->arrows, tokens[i]);
			i++;
			com->file = ft_array_realloc(com->file, tokens[i]);
		}
		else if (ft_strcmp(tokens[i], "|") == 0 || ft_strcmp(tokens[i], ";") == 0)
		{
			com->pipe_sc = tokens[i][0];
			//printf("pipe_sc is %c\n", com->pipe_sc);
			//tokens = tokens->next;
			i++;
			break ;
		}
		else
		{
			//printf("arg is %s\n", tokens[i]);
			arg = tokens[i];
			if (!(arg = edit_arg(arg, conf)))
				error_quit("Invalid argument", conf);
			com->args = ft_array_realloc(com->args, arg);
			free(arg);
		}
		i++;
	}
	ft_comadd_back(&(conf->command), com);
	//printf("com added\n");
	return (i);
}

void	analyze_tokens(t_struct *conf, char **tokens)
{
	//char	*token;
	int		i;

	i = 0;
	while (tokens[i])
	{
		//printf("our token is %s\n", tokens[i]);
		if (ft_strcmp(tokens[i], ":") == 0 || ft_strcmp(tokens[i], "|") == 0)
		{
			conf->betweens = ft_array_realloc(conf->betweens, tokens[i]);
			i++;
		}
		else
		{
			//printf("hey command\n");
			i = i + create_command(&tokens[i], conf); // ----------------------edit
			//printf("command created\n");
		}
	}
	//clear_tokens(conf);
	//printf("analyze finished\n");
}