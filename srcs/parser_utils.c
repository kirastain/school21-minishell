/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 23:41:15 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 11:32:22 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*delete_quotes(char *token)
{
	char	*new;
	char	*old;
	int		len;

	old = token;
	len = ft_strlen(old);
	new = ft_substr(old, 1, len - 2);
	return (new);
}
