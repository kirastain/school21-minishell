/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 01:10:09 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/12 01:39:32 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (line[i] == '\"')
			flag_double++;
		else if (line[i] == "\'")
			flag_single++;
		i++;
	}
	if (flag_double % 2 != 0 || flag_single % 2 != 0)
		error_quit("Wrong number of quotes", conf);
	return ;
}