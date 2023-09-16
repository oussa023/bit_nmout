/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:13:48 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 15:14:35 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
		return (i);
	}
	return (0);
}

char	*pwd2(void)
{
	char	buf[PATH_MAX];
	char	*ptr;

	getcwd(buf, sizeof(buf));
	ptr = buf;
	return (ptr);
}

int	search_index(const char *s, int c)
{
	char	*str;
	int		i;
	char	ca;
	int		lend;
	int		jeton;

	str = (char *)s;
	i = 0;
	ca = (char)c;
	lend = ft_strlen(s);
	while (i <= lend)
	{
		if (str[i] == ca)
			return (i);
		i++;
	}
	return (-1);
}

int	echo_norm(char **cmd, int *i, int *j, int *flag)
{
	while (cmd[*i][0] == '-')
	{
		if (cmd[*i][*j] == '\0')
			break ;
		while (cmd[*i][*j] == 'n')
			(*j)++;
		if (cmd[*i][*j - 1] == 'n' && cmd[*i][*j] == '\0')
			*flag = 0;
		if (cmd[*i][*j] != '\0')
			break ;
		(*i)++;
		if (!cmd[*i])
			break ;
		*j = 1;
	}
}

int	echo(char **cmd, int fd)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	j = 1;
	flag = 1;
	if (!cmd[i])
	{
		ft_putstr_fd("\n", fd, 0);
		return (0);
	}
	echo_norm(cmd, &i, &j, &flag);
	while (cmd[i])
	{
		if (cmd[i + 1] == NULL)
			ft_putstr_fd(cmd[i], fd, 0);
		else
			ft_putstr_fd(cmd[i], fd, 1);
		i++;
	}
	if (flag == 1)
		ft_putstr_fd("\n", fd, 0);
	return (exit_stat = 0, 0);
}
