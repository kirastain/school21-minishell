/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 01:10:09 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 19:11:47 by bbelen           ###   ########.fr       */
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
	//char	*finish_line;
	//char	*tmp;

	i = 0;
	flag_double = 0;
	flag_single = 0;
	//finish_line = NULL;
	//finish_line = ft_strdup(line);
	//free(line);
	//tmp = NULL;
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
	/*if (flag_double % 2 != 0)
	{
		printf("error\n");
		while (!(if_in_str(tmp, '\"')))
		{
			printf("line is %s\n", line);
			ft_putstr_fd("finish with quote > ", 1);
			gnl_shell(0, &tmp, conf);
			finish_line = ft_strjoin_free(finish_line, tmp);
			if (if_in_str(tmp, '\"'))
				break ;
		}
	}
	else if (flag_single % 2 != 0)
	{
		//error_quit("Wrong number of quotes", conf);
		//while (!(ft_strchr(finish_line, '\'')))
		//{

		//}
	}
	printf("line is %s\n", finish_line);
	return (&finish_line[0]);*/
}
