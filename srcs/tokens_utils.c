/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:51:27 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/13 02:28:52 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *edit_arg(char *token)
{
	char	*name;

	name = ft_strdup(token);
	return (name);
}

int	if_command_name(char *token)
{
	if (token)
		return (1);
	return (0);
}

void	ft_comadd_back(t_command **lst, t_command *new)
{
	t_command	*current;

	if (!(*lst))
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

int	is_command_end(char *token)
{
	if (ft_strcmp(token, ";") == 0)
		return (1);
	if (ft_strcmp(token, "|") == 0)
		return (1);
	if (ft_strcmp(token, ">") == 0)
		return (1);
	if (ft_strcmp(token, "<") == 0)
		return (1);
	if (ft_strcmp(token, ">>") == 0)
		return (1);
	return (0);
}