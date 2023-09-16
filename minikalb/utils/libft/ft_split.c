/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:45:05 by okassimi          #+#    #+#             */
/*   Updated: 2022/11/16 03:42:32 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	mama;

	i = 0;
	mama = 0;
	while (s[i] == c)
	{
		i++;
	}
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			mama++;
		i++;
	}
	return (mama);
}

static void	ft_skip(char c, char const *s, int *pos0, int *pos1)
{
	while ((s[*pos0 + *pos1]) == c && (s[*pos0 + *pos1]))
		(*pos0)++;
}

static char	**oussa(char **result, int k)
{
	while (k >= 0)
	{
		free (result[k]);
		k--;
	}
	free(result);
	return (0);
}
// i    j    k   count 

struct s_pouss {
	int		v[4];
	char	**p;
} pos;

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (0);
	ft_memset(pos.v, 0, 16);
	pos.v[3] = ft_count(s, c);
	pos.p = ft_calloc(pos.v[3] + 1, sizeof(char *));
	if (!pos.p)
		return (0);
	ft_skip(c, s, &pos.v[0], &pos.v[1]);
	while (s[pos.v[0]] != '\0')
	{
		if (s[pos.v[0] + pos.v[1]] == c || s[pos.v[0] + pos.v[1]] == '\0')
		{
			pos.p[pos.v[2]] = ft_substr(s, pos.v[0], pos.v[1]);
			if (!pos.p[pos.v[2]])
				return (oussa(pos.p, pos.v[2]));
			pos.v[2]++;
			pos.v[0] = pos.v[0] + pos.v[1];
			pos.v[1] = 0;
		}
		ft_skip(c, s, &pos.v[0], &pos.v[1]);
		if (s[pos.v[0] + pos.v[1]] && s[pos.v[0] + pos.v[1]] != c)
			pos.v[1]++;
	}
	return (pos.p);
}
