/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:53:43 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 19:21:04 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_error(char *str, t_struct *conf)
{
	char	*str_error;
	char	*tmp;

	str_error = ft_strdup("syntax error near unexpected token \'");
	tmp = str_error;
	str_error = ft_strjoin(str_error, str);
	free(tmp);
	tmp = str_error;
	str_error = ft_strjoin(str_error, "\'");
	free(tmp);
	error_quit(str_error, conf);
}

void	simple_quit(void)
{
	ft_putstr_fd("\n", 1);
	exit(1);
}

void	error_code(char *com, int code)
{
	char	*response;

	response = NULL;
	response = ft_strjoin(com, ": ");
	if (code == -5)
		response = ft_strjoin(response, "command not found");
	else
		response = ft_strjoin(response, (char *)strerror(code));
	response = ft_strjoin(response, "\n");
	ft_putstr_fd(response, 1);
	if (response)
		free(response);
}

void	error_quit(char *str, t_struct *conf)
{
	g_error = "1";
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	clear_conf(conf);
	read_shell_line(conf);
}
