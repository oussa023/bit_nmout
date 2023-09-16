/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:53:49 by okassimi          #+#    #+#             */
/*   Updated: 2022/11/17 08:56:04 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*pt;
	size_t			i;

	pt = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		pt[i] = (unsigned char)c;
		i++;
	}
	return (str);
}
