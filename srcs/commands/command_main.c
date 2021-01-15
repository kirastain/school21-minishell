/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:52:26 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 21:59:34 by bbelen           ###   ########.fr       */
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
	{
		//printf("------------------to pwd\n");
		pwd_command(com, conf);
	}
	else if (ft_strcmp(com->name, "env") == 0)
	{
		//printf("------------------to env\n");
		env_command(com, conf->env, conf);
	}
	else if (ft_strcmp(com->name, "export") == 0)
	{
		//printf("---------------to export\n");
		export_command(com, conf);
	}
	else if (ft_strcmp(com->name, "exit") == 0)
	{
		//printf("------------to exit\n");
		exit_command(conf);
	}
	else if (ft_strcmp(com->name, "cd") == 0)
	{
		//printf("--------------to cd\n");
		cd_command(com, conf);
	}
	else if (ft_strcmp(com->name, "unset") == 0)
	{
		//printf("-----------to unset\n");
		unset_command(com, conf);
	}
	else if (ft_strcmp(com->name, "echo") == 0)
	{
		//printf("--------------to echo\n");
		echo_command(com, conf);
	}
	else if (ft_strcmp(com->name, ">") == 0)
	{
		//printf("------------to redirect\n");
	}
	else if (ft_strcmp(com->name, "$?") == 0)
	{
		//printf("---------------error output\n");
		get_current_error();
	}
	else
	{
		//printf("----------------to outsource\n");
		outsource(com, conf);
	}
	//printf("hub finished\n");
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
		//printf("com main start %s and %c\n", com->name, com->pipe_sc);
		if (com->pipe_sc == '|')
		{
			pipes = count_pipes(com);
			//printf("num of pipes is %d", pipes);
			init_command_array(conf, pipes);
			com = pipes_command(conf, com);
			do_pipes(conf, pipes);
			clear_command_array(conf, pipes);
		}
		else
		{
			//printf("to com hub\n");
			command_hub(com, conf);
			//printf("finished %s\n", com->name);
			com = com->next;
		}
	}
	//printf("finished %s\n", conf->command->name);
}
