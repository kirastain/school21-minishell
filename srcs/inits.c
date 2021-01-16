/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:05:06 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 11:32:45 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		init_betweens(t_struct *conf)
{
	if (!(conf->betweens = (char **)malloc(sizeof(char *) * 1)))
		error_quit("Memory issue", conf);
	conf->betweens[0] = NULL;
	if (!(conf->tokens = (char **)malloc(sizeof(char *) * 1)))
		error_quit("Memory issue", conf);
	conf->tokens[0] = NULL;
}

void		init_conf(t_struct *conf)
{
	conf->env = NULL;
	conf->command_array = NULL;
	conf->command = NULL;
	conf->tokens = NULL;
	conf->curr_command = NULL;
	if (!(conf->export = (char**)malloc(sizeof(char*) * 1)))
		error_quit("Memory issue", conf);
	conf->export[0] = NULL;
	conf->betweens = NULL;
}

void		init_command_array(t_struct *conf, int pipes)
{
	if (!(conf->arr = (char***)malloc(sizeof(char**) * pipes)) ||
		!(conf->arr_int = (int*)malloc(sizeof(int) * pipes)) ||
		!(conf->command_array =
			(t_command**)malloc(sizeof(t_command*) * pipes)))
		error_quit("Memory issue", conf);
}

t_command	*init_command(t_struct *conf)
{
	t_command	*com;

	if (!(com = (t_command*)malloc(sizeof(t_command))))
		error_quit("Memory issue", conf);
	if (!(com->args = (char**)malloc(sizeof(char*) * 1)))
		error_quit("Memory issue", conf);
	com->args[0] = NULL;
	if (!(com->file = (char**)malloc(sizeof(char*) * 1)))
		error_quit("Memory issue", conf);
	com->file[0] = NULL;
	if (!(com->arrows = (char**)malloc(sizeof(char*) * 1)))
		error_quit("Memory issue", conf);
	com->arrows[0] = NULL;
	com->name = NULL;
	com->next = NULL;
	com->pipe_sc = '\0';
	return (com);
}
