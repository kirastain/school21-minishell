/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 01:10:09 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 20:42:23 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		error_quit("Wrong number of quotes\n", conf);
}
