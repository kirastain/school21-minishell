/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_fills.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 13:51:19 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 19:54:01 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_com_name(t_command *com, char *token, int *flag_name)
{
	com->name = ft_strdup(token);
	if (com->name[0] == '\"' || com->name[0] == '\'')
		com->name = delete_quotes(com->name);
	*flag_name = 1;
}

int		fill_arrows_case(t_command *com, char **tokens, int *flag_name)
{
	com->name = ft_strdup(">");
	*flag_name = 1;
	return (fill_arrows(com, tokens));
}

int		fill_arrows(t_command *com, char **tokens)
{
	int	i;

	i = 0;
	com->arrows = ft_array_realloc(com->arrows, tokens[i]);
	i++;
	com->file = ft_array_realloc(com->file, tokens[i]);
	return (i);
}

int		fill_pipe_sc(t_command *com, char *token, t_struct *conf, int i)
{
	com->pipe_sc = token[0];
	ft_comadd_back(&(conf->command), com);
	i++;
	return (i);
}

void	fill_arg(t_command *com, char *token, t_struct *conf)
{
	char	*arg;

	arg = NULL;
	if (ft_strcmp(token, "\'\'") == 0 || ft_strcmp(token, "\"\"") == 0)
		arg = ft_strdup("");
	else
	{
		arg = token;
		arg = edit_arg(arg, conf);
		if (!arg)
			error_quit("invalid argument", conf);
	}
	com->args = ft_array_realloc(com->args, arg);
	free(arg);
}
