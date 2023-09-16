/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   U_tokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:06:43 by okassimi          #+#    #+#             */
/*   Updated: 2023/09/11 11:03:47 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

int _is_param(t_node *node)
{
	if (node->type == PIPE_LINE ||node->type == REDIR_APPAND || node->type == REDIR_HERDOC || node->type == REDIR_OUTPUT
	|| node->type == REDIR_INPUT)
		return (1);
	return (0);
}

int	_is_special(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int _is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	_is_quoted(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int _search_index(const char *s, int c)
{
	char	*str;
	int		i;
	char	ca;
	int		lend;
    int     jeton;

	str = (char *)s;
	i = 0;
	ca = (char)c;
	lend = ft_strlen(s);
	jeton = 1;
	while (i <= lend)
	{
		if (str[i] == ca)
			return (jeton);
		i++;
	}
	return (0);
}