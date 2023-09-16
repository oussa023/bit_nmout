/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:47:54 by okassimi          #+#    #+#             */
/*   Updated: 2022/11/16 07:08:16 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int					i;
	int					signe;
	long long			nb;

	i = 0;
	nb = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		signe *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] && (nptr[i] >= 48 && nptr[i] <= 57))
	{
		if (nb > 9223372036854775807 && signe == -1)
			return (0);
		if (nb > 9223372036854775807 && signe == 1)
			return (-1);
		nb = nb * 10 + nptr[i++] - '0';
	}
	return (nb * signe);
}
