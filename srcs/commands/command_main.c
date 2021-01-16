/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:52:26 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 11:46:41 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_current_error(void)
{
	ft_putstr_fd(ft_strjoin(g_error, ": command not found\n"), 1);
	g_error = "127";
}

void	command_hub(t_command *com, t_struct *conf)
{
	if (ft_strcmp(com->name, "pwd") == 0)
		pwd_command(com, conf);
	else if (ft_strcmp(com->name, "env") == 0)
		env_command(com, conf->env, conf);
	else if (ft_strcmp(com->name, "export") == 0)
		export_command(com, conf);
	else if (ft_strcmp(com->name, "exit") == 0)
		exit_command(conf);
	else if (ft_strcmp(com->name, "cd") == 0)
		cd_command(com, conf);
	else if (ft_strcmp(com->name, "unset") == 0)
		unset_command(com, conf);
	else if (ft_strcmp(com->name, "echo") == 0)
		echo_command(com, conf);
	else if (ft_strcmp(com->name, "$?") == 0)
		get_current_error();
	else
		outsource(com, conf);
}

int		count_pipes(t_command *coms)
{
	t_command	*com;
	int			count;

	count = 1;
	com = coms;
	while (com && com->pipe_sc == '|')
	{
		count++;
		com = com->next;
	}
	return (count);
}

void	command_main(t_struct *conf)
{
	int			pipes;
	t_command	*com;

	com = conf->command;
	if (!com)
		return ;
	while (com)
	{
		if (com->pipe_sc == '|')
		{
			pipes = count_pipes(com);
			init_command_array(conf, pipes);
			com = pipes_command(conf, com);
			do_pipes(conf, pipes);
			clear_command_array(conf, pipes);
		}
		else
		{
			command_hub(com, conf);
			com = com->next;
		}
	}
}
