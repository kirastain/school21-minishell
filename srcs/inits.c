/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:05:06 by bbelen            #+#    #+#             */
/*   Updated: 2020/11/22 19:04:38 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    init_conf(t_struct *conf)
{
    conf->shell_line = NULL;
    conf->signal = 0;
    if (!(conf->command = (t_command*)malloc(sizeof(t_command))))
        exit(-1);
}