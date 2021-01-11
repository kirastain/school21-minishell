/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:53:43 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/11 13:48:47 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	output_error(char *str)
{
	ft_putstr_fd("bash: syntax error near unexpected token \'", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\'\n", 1);
	return (0);
}

void	error_quit(char *str, t_struct *conf)
{
	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	//clear
	shell_line(conf);
}