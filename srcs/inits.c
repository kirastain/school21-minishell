/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:05:06 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/13 19:24:22 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    init_conf(t_struct *conf)
{
    conf->env = NULL;
    conf->command_array = NULL;
    conf->command = NULL;
	conf->tokens = NULL;
	if (!(conf->export = (char **)malloc(sizeof(char *) * 1)) ||
		!(conf->betweens = (char **)malloc(sizeof(char *) * 1)))
		error_quit("Memory issue\n", conf);
	conf->export[0] = NULL;
	conf->betweens[0] = NULL;

}

t_command    *init_command(t_struct *conf)
{
    t_command   *com;
    
    if (!(com = (t_command*)malloc(sizeof(t_command))))
        error_quit("Memory issue\n", conf);
    com->args = (char**)malloc(sizeof(char*) * 1); //после убрать, память выделять надо в другом месте
    com->args[0] = NULL;
    if (!(com->file = (char **)malloc(sizeof(char *) * 1)))
		error_quit("Memory issue", conf);
	com->file[0] = NULL;
	if (!(com->arrows = (char **)malloc(sizeof(char *) * 1)))
		error_quit("Memory issue", conf);
    com->name = NULL;
    com->next = NULL;
	com->pipe_sc = '\0';
    return (com);
}