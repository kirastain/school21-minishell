/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:52:26 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/12 17:09:56 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	command_hub(t_command *com, t_struct *conf)
{
	if (ft_strcmp(com->name, "pwd") == 0)
    	pwd_command(com);
	else if (ft_strcmp(com->name, "env") == 0)
        env_command(com, conf->env);
	else if (ft_strcmp(com->name, "export") == 0)
		export_command(com, conf);
	else if (ft_strcmp(com->name, "exit") == 0)
		exit_command(conf);
	else if (ft_strcmp(com->name, "cd") == 0)
		cd_command(com, conf);
	else if (ft_strcmp(com->name, "unset") == 0)
		unset_command(com, conf);
	else if (ft_strcmp(com->name, "echo") == 0)
		echo_command(com);
	else
		outsource(com, conf);	
}

void	command_main(t_struct *conf)
{
	conf->command = *(conf->command_array);
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
			command_hub(conf->command, conf);
			conf->command = conf->command->next;
		}
	}
}