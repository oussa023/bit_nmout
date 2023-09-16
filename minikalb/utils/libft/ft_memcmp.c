/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:43:30 by okassimi          #+#    #+#             */
/*   Updated: 2022/11/17 08:25:31 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*pt1;
	unsigned char	*pt2;
	size_t			i;

	pt1 = (unsigned char *)s1;
	pt2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (!(pt1[i] == pt2[i]))
		{
			return (pt1[i] - pt2[i]);
		}
		i++;
	}
	return (0);
}
