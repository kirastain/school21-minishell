/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 15:11:21 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 13:14:29 by bbelen           ###   ########.fr       */
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

int		checking_flag(char *line, int *i, int flag)
{
	if ((line[*i] == '\"' || line[*i] == '\'') && (!line[*i - 1] ||
				line[*i - 1] != '\\') && !flag)
		return (1);
	else if ((line[*i] == '\"' || line[*i] == '\'') && (!line[*i - 1] ||
				line[*i - 1] != '\\') && flag)
		return (0);
	return (flag);
}

void	checking_line(char *line, t_struct *conf)
{
	int	i;
	int	flag;

	i = 0;
	check_quotes(&line[i], conf);
	while ((line[i] == ' ' || line[i] == 9) && line[i] != '\0')
		i++;
	if (line[i] == '|')
		output_error("|", conf);
	else if (line[i] == ';')
		output_error(";", conf);
	while (line[i] != '\0')
	{
		flag = checking_flag(&line[i], &i, flag);
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
}
