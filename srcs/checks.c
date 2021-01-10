/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 15:11:21 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/10 20:24:00 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_for_pc_vertline(char *line)
{
    int i;

    i = 1;
    while ((line[i] == ' ' || line[i] == 9) && line[i] != '\0')
        i++;
    if (line[i] == ';')
		return output_error(";");
	else if (line[i] == '|')
		return output_error("|");
	return (1);
}

int check_streams(char *line)
{
    int i;

    i = 1;
    if (line[i - 1] == '>' && line[i + 1] == '>')
    {
		i++;
        while ((line[i] == ' ' || line[i] == 9) && line[i] != '\0')
            i++;
        if (line[i] == '>')
			return output_error(">");
		else if (line[i] == '<')
            return output_error("<");
    }
    else if (line[i - 1] == '>')
    {
        while ((line[i] == ' ' || line[i] == 9) && line[i] != '\0')
            i++;
        if (line[i] == '<')
			return output_error("<");
		else if (line[i] == '>')
            return output_error(">");
    }
    else
    {
        while ((line[i] == ' ' || line[i] == 9) && line != '\0')
            i++;
        if (line[i] == '>')
			return output_error(">");
		else if (line[i] == '<')
			return output_error("<");
		else if (line[i] == '|')
            return output_error("|");
    }
    return (1);
}

void    check_after_vertline(char *line)
{
    int i;

    i = 0;
    while ((line[i] == ' ' || line[i] == 9) && line[i] != '\0')
        i++;
    if (!line[i])
        printf("write next function\n");
}

int checking_line(char *line)
{
    int i;
    int check;

    i = 0;
    check = 1;
    while ((line[i] == ' ' || line[i] == 9) && line[i] != '\0')
        i++;
    if (line[i] == '|')
        return (0);
    while (line[i] != '\0' && check)
    {
        if (line[i] == ';' || line[i] == '|')
            check = check_for_pc_vertline(&line[i]);
        if (line[i] == '>' || line[i] == '<' || (line[i] == '>' && line[i + 1] == '>'))
            check = check_streams(&line[i]);
        if (line[i] == '|')
            check_after_vertline(&line[i]);
        i++;
    }
    return (check);
}