/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:30:31 by okassimi          #+#    #+#             */
/*   Updated: 2023/09/10 00:19:13 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	p = malloc((ft_strlen(s1) + ft_strlen(s2)) * (sizeof(char) + 1));
	if (!p)
		return (0);
	j = 0;
	if (i < (ft_strlen(s1)+ft_strlen(s2)))
	{
		while (i < ft_strlen(s1))
			p[i++] = s1[j++];
		j = 0;
		while (i < (ft_strlen(s1) + ft_strlen(s2)))
			p[i++] = s2[j++];
	}
	p[i] = '\0';
	return (p);
}

