/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:37:04 by bbelen            #+#    #+#             */
/*   Updated: 2020/12/10 18:38:55 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    write_command(t_command *command, char *response)
{
    if (command)
        ft_putstr_fd(response, 0);
}