/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:33:40 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/13 01:18:00 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*create_command(t_list *tokens, t_struct *conf)
{
	t_command	*com;
	int			flag_name;
	char		*arg;

	com = NULL;
	com = init_command();
	arg = NULL;
	flag_name = 0;
	if (!(com = init_command(com)))
		error_quit("Memory issue");
	while (!(is_command_end(tokens->content)))
	{
		if (flag_name == 0 && if_command_name(tokens->content))
		{
			com->name = ft_strdup(tokens->content);
			flag_name = 1;
		}
		if (!(arg = edit_arg(tokens->content)))
			error_quit("Invalid argument\n", conf);
		com->args = ft_array_realloc(com->args, arg);
		if (arg)
			free(arg);
		tokens = tokens->next;
	}
	conf->command_array = ft_com_add(conf->command_array, com);
	return (tokens);
}

void	analyze_tokens(t_struct *conf, t_list *tokens)
{
	char	*token;

	while (tokens)
	{
		token = tokens->content;
		if (ft_strcmp(token, ":") == 0 || ft_strcmp(token, "|") == 0)
		{
			conf->betweens = ft_array_realloc(conf->betweens, tokens->content);
		}
		else
		{
			tokens = create_command(tokens, conf);
		}
		tokens = tokens->next;
	}
}