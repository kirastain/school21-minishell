/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outsource.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:10:13 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/12 17:20:05 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	outsource(t_command *com, t_struct *conf)
{
	printf("outsource %s\n", com->name);
	printf("%d\n", conf->error);
}