/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:51:27 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 00:03:10 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*edit_arg(char *token, t_struct *conf)
{
	int			i;
	char		*tmp;
	char		*res;

	tmp = NULL;
	i = 0;
	if (token[0] == '\'')
		tmp = edit_arg_2(token, conf->env, 1);
	else if (token[0] == '\"')
		tmp = edit_arg_2(token, conf->env, 2);
	else
		tmp = edit_arg_2(token, conf->env, 0);
	res = tmp;
	return (res);
}

int		if_command_name(char *token, char *path)
{
	if (token && path)
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

int		is_command_end(char *token)
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
