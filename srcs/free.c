/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 01:01:24 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 23:31:53 by bbelen           ###   ########.fr       */
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

/*
void	clear_command(t_command *coms)
{
	g_flag = 0;
	if (!coms)
		return ;
	printf("clear command\n");
	free(coms->name);
	if (coms->file)
		ft_array_free(coms->file);
	if (coms->args)
		ft_array_free(coms->args);
	if (coms->arrows)
		ft_array_free(coms->arrows);
	free(coms);
}
*/

void	clear_command(t_command *coms)
{
	t_command	*com;

	g_flag = 0;
	while (coms)
	{
		printf("clear command\n");
		com = coms->next;
		free(coms->name);
		printf("cleared name\n");
		ft_array_free(coms->file);
		printf("cleared file\n");
		printf("arg is\n");
		//ft_array_free(com->args);
		printf("cleared args\n");
		//ft_array_free(com->arrows);
		printf("cleared arrows\n");
		free(coms);
		coms = com;
		printf("clear done\n");
	}
}

void	clear_tokens(t_struct *conf)
{
	t_list	*current;
	//char	*clean;

	if (!conf || !(conf->tokens))
		return ;
	while (conf->tokens)
	{
		current = conf->tokens->next;
		//clean = conf->tokens->content;
		//free((void*)clean);
		printf("t_list token is %s\n", conf->tokens->content);
		printf("t_list token is %s\n", conf->tokens->next->content);
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
	t_command		*com;

	g_flag = 0;
	if (conf->command != NULL)
	{
		while (conf->command)
		{
			com = conf->command->next;
			printf("done\n");
			ft_array_free(conf->command->file);
			printf("done\n");
			ft_array_free(conf->command->arrows);
			printf("done\n");
			ft_array_free(conf->command->args);
			printf("done\n");
			free(conf->command->name);
			free(conf->command);
			conf->command = com;
			printf("done\n");
		}
	}
	if (conf->betweens != NULL)
		ft_array_free(conf->betweens);
	printf("done\n");
	if (conf->tokens != NULL)
		clear_tokens(conf);
	printf("all done\n");

}
