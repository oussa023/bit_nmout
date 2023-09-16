/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:22:26 by okassimi          #+#    #+#             */
/*   Updated: 2022/11/17 08:48:46 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dstt;
	char	*srct;
	size_t	i;

	srct = (char *)src;
	dstt = (char *)dst;
	i = 0;
	if (!src && !dst)
		return (0);
	while (i < n)
	{
		dstt[i] = srct[i];
		i++;
	}
	return (dst);
}
