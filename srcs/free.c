/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 01:01:24 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 15:59:17 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_command_array(t_struct *conf, int pipes)
{
	int i;

	i = 0;
	while (i < pipes)
	{
		if (conf->arr[i] != NULL)
			ft_array_free(conf->arr[i]);
		else
			free(conf->arr[i]);
		i++;
	}
	if (conf->arr_int)
		free(conf->arr_int);
	if (conf->arr)
		free(conf->arr);
	free(conf->command_array);
}

void	clear_command(t_command *coms)
{
	t_command	*com;

	if (!coms)
		return ;
	while (coms)
	{
		com = coms->next;
		if (coms->name)
			free(coms->name);
		if (coms->file)
			ft_array_free(coms->file);
		if (com->args)
			ft_array_free(com->args);
		if (com->arrows)
			ft_array_free(com->arrows);
		free(coms);
		coms = com;
	}
}

void	clear_tokens(t_struct *conf)
{
	t_list	*current;

	if (!conf || !(conf->tokens))
		return ;
	while (conf->tokens)
	{
		current = conf->tokens->next;
		free(conf->tokens->content);
		free(conf->tokens);
		conf->tokens = current;
	}
}

void	clear_env_export(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}

void	clear_conf(t_struct *conf)
{
	g_flag = 0;
	if (g_shell_line)
		free(g_shell_line);
	printf("shell_line cleared\n");
	if (conf->tokens)
		clear_tokens(conf);
	printf("tokens cleared\n");
	clear_env_export(conf->env);
	if (conf->export)
		clear_env_export(conf->export);
}
