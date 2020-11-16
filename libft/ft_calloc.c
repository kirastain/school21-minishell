/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:34:58 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/20 22:24:01 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(size * nmemb);
	if (!p)
		return (p);
	ft_bzero(p, size * nmemb);
	return (p);
}
