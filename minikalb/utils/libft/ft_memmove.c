/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 23:48:39 by okassimi          #+#    #+#             */
/*   Updated: 2022/11/17 08:56:43 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*dstt;
	char	*srct;
	int		j;
	int		i;

	srct = (char *)src;
	dstt = (char *)dst;
	j = n;
	i = 0;
	if (!src && !dst)
		return (0);
	if (!srct[i] && !dstt[i])
		return (dst);
	if (dstt < srct)
		ft_memcpy(dst, src, n);
	else
	{
		while (n != 0 && j != 0)
		{
			dstt[j - 1] = srct[n - 1];
			n--;
			j--;
		}
	}
	return (dstt);
}
