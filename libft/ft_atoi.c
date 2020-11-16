/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:49:46 by bbelen            #+#    #+#             */
/*   Updated: 2020/05/17 18:43:43 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_overlap(int sign)
{
	if (sign == -1)
		return (0);
	return (-1);
}

int				ft_atoi(const char *nptr)
{
	long long	nb;
	int			sign;

	nb = 0;
	sign = 1;
	while (*nptr != '\0' && ((*nptr >= 9
					&& *nptr <= 13) || *nptr == ' '))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr != '\0' && (*nptr >= 48 && *nptr <= 57))
	{
		if (nb > nb * 10 + (*nptr - '0') && nb != 214748364)
			return (ft_overlap(sign));
		nb = (nb * 10) + (*nptr - '0');
		nptr++;
	}
	return ((int)nb * sign);
}
