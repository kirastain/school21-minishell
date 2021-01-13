/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:52:26 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 01:45:39 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_current_error(t_struct *conf)
{
	ft_putstr_fd(ft_strjoin(conf->error, ": command not found\n"), 1);
	conf->error = ft_strdup("127");
}

void	command_hub(t_command *com, t_struct *conf)
{
	if (ft_strcmp(com->name, "pwd") == 0)
	{
		printf("------------------to pwd\n");
    	pwd_command(com, conf);
	}
	else if (ft_strcmp(com->name, "env") == 0)
	{
		printf("------------------to env\n");
        env_command(com, conf->env, conf);
	}
	else if (ft_strcmp(com->name, "export") == 0)
	{
		printf("---------------to export\n");
		export_command(com, conf);
	}
	else if (ft_strcmp(com->name, "exit") == 0)
	{
		printf("------------to exit\n");
		exit_command(conf);
	}
	else if (ft_strcmp(com->name, "cd") == 0)
	{
		printf("--------------to cd\n");
		cd_command(com, conf);
	}
	else if (ft_strcmp(com->name, "unset") == 0)
	{
		printf("-----------to unset\n");
		unset_command(com, conf);
	}
	else if (ft_strcmp(com->name, "echo") == 0)
	{
		printf("--------------to echo\n");
		echo_command(com, conf);
	}
	else if (ft_strcmp(com->name, ">") == 0)
	{
		printf("------------to redirect\n");
		//redirect_arrow_command(com, conf);
	}
	else if (ft_strcmp(com->name, "$?") == 0)
	{
		printf("---------------error output\n");
		get_current_error(conf);
	}
	else
	{
		printf("----------------to outsource\n");
		outsource(com, conf);	
	}
}

int		count_pipes(t_struct *conf)
{
	t_command	*com;
	int			count;

	count = 1;
	com = conf->command;
	while (com && com->pipe_sc == '|')
	{
		count++;
		com = com->next;
	}
	return (count);
}

void	command_main(t_struct *conf)
{
	int	pipes;

	if (!(conf->command))
		return ;
	while (conf->command)
	{
		if (conf->command->pipe_sc == '|')
		{
			pipes = count_pipes(conf);
			init_command_array(conf, pipes);
			conf->command = pipes_command(conf, conf->command);
			do_pipes(conf, pipes);
			clear_command_array(conf, pipes); //to do
		}
		else
		{
			command_hub(conf->command, conf);
			conf->command = conf->command->next;
		}
	}
}