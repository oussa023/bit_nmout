/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:55:33 by okassimi          #+#    #+#             */
/*   Updated: 2022/11/14 09:30:29 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;
	char	ca;
	int		lend;

	str = (char *)s;
	i = 0;
	ca = (char)c;
	lend = ft_strlen(s);
	while (i <= lend)
	{
		if (str[i] == ca)
			return (str + i);
		i++;
	}
	return (0);
}
