/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 01:10:09 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 13:14:06 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_double_stream(char *line, t_struct *conf)
{
	int	i;

	i = 2;
	while ((line[i] == ' ' || line[i] == 9) && line[i] != '\0')
		i++;
	if (line[i] == '>')
		output_error(">", conf);
	else if (line[i] == '<')
		output_error("<", conf);
	return ;
}

void	check_streams(char *line, t_struct *conf)
{
	int i;

	i = 1;
	if (line[i - 1] == '>')
	{
		while ((line[i] == ' ' || line[i] == 9) && line[i] != '\0')
			i++;
		if (line[i] == '<')
			output_error("<", conf);
		else if (line[i] == '>')
			output_error(">", conf);
	}
	else
	{
		while ((line[i] == ' ' || line[i] == 9) && line != '\0')
			i++;
		if (line[i] == '>')
			output_error(">", conf);
		else if (line[i] == '<')
			output_error("<", conf);
		else if (line[i] == '|')
			output_error("|", conf);
	}
	return ;
}

void	check_after_vertline(char *line, t_struct *conf)
{
	int i;

	i = 0;
	while ((line[i] == ' ' || line[i] == 9) && line[i] != '\0')
		i++;
	if (!line[i])
		error_quit("Pipeline in the end of the line", conf);
	return ;
}

int		if_in_str(char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	check_quotes(char *line, t_struct *conf)
{
	int	i;
	int	flag_double;
	int	flag_single;

	i = 0;
	flag_double = 0;
	flag_single = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"' && line[i - 1] != '\\')
			flag_double++;
		else if (line[i] == '\'' && line[i - 1] != '\\')
			flag_single++;
		i++;
	}
	if (flag_double % 2 != 0 || flag_single % 2 != 0)
		error_quit("Wrong number of quotes", conf);
}
