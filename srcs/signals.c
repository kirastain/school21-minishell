/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 21:22:54 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/10 21:31:53 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	work_signals(int sgnl)
{
	if (sgnl == SIGINT)
	{
		ft_putstr_fd("\n", 1);
	}
	else if (sgnl == SIGQUIT)
	{
		ft_putstr_fd("Exit\n", 1);
	}
}