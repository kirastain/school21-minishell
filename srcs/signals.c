/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 21:22:54 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/13 21:19:33 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	work_signals(int sgnl)
{
	if (g_signal == 2)
	{
		g_signal = 1;
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (g_signal == 7)
	{
		g_signal = 8;
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (sgnl == SIGINT)
	{
		if (g_flag == 1)
			ft_putstr_fd("\n", 1);
		else
		{
			ft_putstr_fd("\n", 1);
			ft_putstr_fd(g_shell_line, 1);
		}		
	}
	else if (sgnl == SIGQUIT)
	{
		if (g_flag == 1)
			ft_putstr_fd("Quit\n", 1);
	}
}