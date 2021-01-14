/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:53:43 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 19:04:25 by bbelen           ###   ########.fr       */
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

void	simple_quit(t_struct *conf)
{
	ft_putstr_fd("\n", 1);
	clear_conf(conf);
	exit(1);
}

void	error_code(char *com, int code, t_struct *conf)
{
	char	*response;

	//printf("error code\n");
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
	if (conf->tokens)
		clear_tokens(conf);
	if (conf->command)
		clear_command(conf->command);
	if (g_shell_line)
		free(g_shell_line);
	read_shell_line(conf);
}

void	error_quit(char *str, t_struct *conf)
{
	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	if (conf->tokens)
		clear_tokens(conf);
	if (conf->command)
		clear_command(conf->command);
	if (g_shell_line)
		free(g_shell_line);
	free(conf->command);
	free(conf->tokens);
	read_shell_line(conf);
}
