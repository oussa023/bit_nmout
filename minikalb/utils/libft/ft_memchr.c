/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 22:27:28 by okassimi          #+#    #+#             */
/*   Updated: 2022/11/17 08:49:45 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *str, int c, size_t n)
{
	unsigned char	*pt;
	size_t			i;

	pt = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (pt[i] == (unsigned char)c)
			return (pt + i);
		i++;
	}
	return (0);
}
