/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 01:01:24 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 11:32:28 by bbelen           ###   ########.fr       */
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

	g_flag = 0;
	while (coms)
	{
		com = coms->next;
		free(coms->name);
		ft_array_free(coms->file);
		free(coms);
		coms = com;
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
	t_command		*com;

	g_flag = 0;
	if (conf->command != NULL)
	{
		while (conf->command)
		{
			com = conf->command->next;
			ft_array_free(conf->command->file);
			ft_array_free(conf->command->arrows);
			ft_array_free(conf->command->args);
			free(conf->command->name);
			free(conf->command);
			conf->command = com;
		}
	}
	if (conf->betweens != NULL)
		ft_array_free(conf->betweens);
	ft_array_free(conf->tokens);
}
