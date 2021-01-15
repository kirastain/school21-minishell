/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 15:11:21 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 19:31:17 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_pc_vertline(char *line, t_struct *conf)
{
	int i;

	i = 1;
	while ((line[i] == ' ' || line[i] == 9) && line[i] != '\0')
		i++;
	if (line[i] == ';')
		output_error(";", conf);
	else if (line[i] == '|')
		output_error("|", conf);
	return ;
}

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

void	checking_line(char *line, t_struct *conf)
{
	int	i;
	int	flag;

	i = 0;
	check_quotes(&line[i], conf);
	//printf("%s\n", line);
	while ((line[i] == ' ' || line[i] == 9) && line[i] != '\0')
		i++;
	if (line[i] == '|')
		output_error("|", conf);
	else if (line[i] == ';')
		output_error(";", conf);
	while (line[i] != '\0')
	{
		if ((line[i] == '\"' || line[i] == '\'') && (!line[i - 1] || line[i - 1] != '\\') && !flag)
			flag = 1;
		else if ((line[i] == '\"' || line[i] == '\'') && (!line[i - 1] || line[i - 1] != '\\') && flag)
			flag = 0;
		if (flag && (line[i] == ';' || line[i] == '|'))
			check_for_pc_vertline(&line[i], conf);
		else if (flag && (line[i] == '>' && line[i + 1] == '>'))
			check_double_stream(&line[i], conf);
		else if (flag && (line[i] == '>' || line[i] == '<'))
			check_streams(&line[i], conf);
		else if (flag && line[i] == '|')
			check_after_vertline(&line[i], conf);
		i++;
	}
	//printf("check ok\n");
}
