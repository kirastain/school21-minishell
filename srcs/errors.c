/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:53:43 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/12 01:46:49 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_error(char *str, t_struct *conf)
{
	char	*str_error;
	char	*tmp;

	str_error = ft_strdup("bash: syntax error near unexpected token \'");
	tmp = str_error;
	str_error = ft_strjoin(str_error, str);
	free(tmp);
	tmp = str_error;
	str_error = ft_strjoin(str_error, "\'");
	free(tmp);
	error_quit(str_error, conf);
}

void	error_quit(char *str, t_struct *conf)
{
	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	shell_line(conf);
}