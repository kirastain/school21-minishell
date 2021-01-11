/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 01:01:24 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/11 17:30:59 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_command(t_command **coms)
{
	t_command	*com;
	if (!coms)
		return ;
	while(*coms)
	{
		com = (*coms)->next;
		free((*coms)->name);
		free((*coms)->file_in);
		free((*coms)->file_out);
		free(*coms);
		if (*com->spaces)
			clear_env_export(com->spaces);
		*coms = com;
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
	if(arr)
		free(arr);
}

void	clear_conf(t_struct *conf)
{
	free(conf->shell_line);
	clear_tokens(conf);
	clear_command(conf->command_array);
	clear_env_export(conf->env);
	if (conf->export)
		clear_env_export(conf->export);
}