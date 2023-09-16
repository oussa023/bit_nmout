/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 02:11:06 by okassimi          #+#    #+#             */
/*   Updated: 2023/09/11 11:59:21 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

char	*_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (!s1)
	{
		p = ft_strdup(s2);
		return (p);
	}
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
	free((char *)s1);
	return (p);
}

char *_join_char(char *str, char cara)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(str);
	new = malloc((len + 2) * sizeof(char));
	if (!str)
	{
		new[0] = cara;
		new[1] = 0;
		return (new);
	}
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = cara;
	new[i + 1] = 0;
	return (new);
}

char	*_extract_quoted(char *str,  t_list *env)
{
	char *new_sec;
	char *tmp;
	char *toto;
	int i;
	int	j;
	int len;
	
	i = 0;
	j = 1;
	len = 0;
	int count = 0;
	new_sec = NULL;
	// if (!(_count_env(str) % 2))
	// 	return (ft_strdup(str));
	// printf("|%s|\n", str);
	while (str[i])
	{
		if (str[i] == ENV && str[i + 1] && str[i + 1] == '?' && !(count % 2))
		{
			toto = ft_itoa(exit_stat);
			new_sec = _strjoin(new_sec, toto);
			free(toto);
			i++;
		}
		else if (str[i] == ENV && str[i + 1] && str[i + 1] != ENV && !(count % 2)) 
		{
			j = i + 1;
			while (str[j] && str[j] != ENV && !_is_whitespace(str[j]))
			{
				j++;
				len++;
			}
			toto = ft_substr(str + i + 1, 0, len);
			// printf("|%s|\n", toto);
			new_sec = _strjoin(new_sec, get_env_value(toto, env));
			free(toto);
			i = j - 1;
			len = 0;
		}
		else
		{
			tmp = new_sec;
			new_sec = _join_char(new_sec, str[i]);
			if (str[i] == ENV)
				count++;
			free(tmp);
		}
		i++;
	}
	return (new_sec);
}
