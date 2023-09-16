/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:38:13 by okassimi          #+#    #+#             */
/*   Updated: 2022/11/14 10:25:40 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	first(char *a, char *b);
static	int	last(char *a, char *b);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	char	*se;
	char	*p;

	if (s1 == NULL)
		return (0);
	s = (char *)s1;
	se = (char *)set;
	p = ft_substr(s1, first(s, se), (last(s, se) - first(s, se) + 1));
	return (p);
}

static int	first(char *a, char *b)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (a[i] && b[j])
	{
		if (a[i] == b[j])
		{
			j = 0;
		}
		else
		{
			j++;
			i--;
		}
		i++;
	}
	return (i);
}

static int	last(char *a, char *b)
{
	int	j;
	int	lent;

	j = 0;
	lent = ft_strlen(a)-1;
	while (lent >= 0 && b[j])
	{
		if (a[lent] == b[j])
		{
			lent--;
			j = 0;
		}
		else
		{
			j++;
		}
	}
	return (lent);
}
