/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:05:40 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/10 18:53:12 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    parser_line(char *line, t_struct *conf)
{
    char    **tokens;
    //char    **spaces;

	if (conf)
		printf("go into parser\n");
    tokens = ft_split(line, ' ');
    if (!checking_line(line))
        return (0);
	return (1);
}