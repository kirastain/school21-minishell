/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 01:01:24 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/11 01:26:55 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_tokens(t_struct *conf)
{
	t_list	*current;

	if (!conf || !(conf->tokens))
		return ;
	while (conf->tokens)
	{
		current = conf->tokens->next;
		free(conf->tokens->content);
		conf->tokens = current;
	}
}

