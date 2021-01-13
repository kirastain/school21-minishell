/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:52:26 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/13 18:33:14 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	command_hub(t_command *com, t_struct *conf)
{
	if (ft_strcmp(com->name, "pwd") == 0)
	{
		printf("------------------to pwd\n");
    	pwd_command(com);
	}
	else if (ft_strcmp(com->name, "env") == 0)
	{
		printf("------------------to env\n");
        env_command(com, conf->env);
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
		echo_command(com);
	}
	else if (ft_strcmp(com->name, ">") == 0)
	{
		printf("------------to redirect\n");
		//redirect_command(com, conf);
	}
	else if (ft_strcmp(com->name, "$?") == 0)
	{
		printf("---------------error output\n");
		//get_current_error(com, conf);
	}
	else
	{
		printf("----------------to outsource\n");
		outsource(com, conf);	
	}
}

void	command_main(t_struct *conf)
{
	if (!(conf->command))
		return ;
	while (conf->command)
	{
		if (conf->command->pipe_sc == '|')
		{
			//zhopa
		}
		else
		{
			printf("to command hub\n");
			command_hub(conf->command, conf);
			conf->command = conf->command->next;
		}
	}
}