/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:32:19 by okassimi          #+#    #+#             */
/*   Updated: 2022/11/13 12:17:29 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d;
	size_t	s;
	size_t	di;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	d = ft_strlen(dst);
	di = ft_strlen(dst);
	s = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (s);
	else if (dstsize <= d)
		return (s + dstsize);
	while (src[i] && d < dstsize - 1)
	{
		dst[d] = src[i];
		i++;
		d++;
	}
	dst[d] = '\0';
	return (di + s);
}
