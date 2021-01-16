/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:33:40 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 13:59:36 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int		if_arrows(char *token)
{
	if (ft_strcmp(token, ">") == 0 ||
			ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">>") == 0)
		return (1);
	return (0);
}

int		if_pipe_sc(char *token)
{
	if (ft_strcmp(token, "|") == 0 ||
			ft_strcmp(token, ";") == 0)
		return (1);
	return (0);
}

int		create_command(char **tokens, t_struct *conf)
{
	t_command	*com;
	int			flag_name;
	int			i;

	flag_name = 0;
	i = -1;
	if (!(com = init_command(conf)))
		error_quit("Memory issue", conf);
	while (tokens[++i])
	{
		if (flag_name == 0)
			fill_com_name(com, tokens[i], &flag_name);
		else if (if_arrows(tokens[i]))
			i += fill_arrows(com, &tokens[i]);
		else if (if_pipe_sc(tokens[i]))
			return (fill_pipe_sc(com, tokens[i], conf, i));
		else
			fill_arg(com, tokens[i], conf);
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
