/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:12:20 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 15:12:22 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

int	check_digit_special(char *str)
{
	int	i;

	i = 0;
	if ((str[0] >= 48 && str[0] <= 57))
		return (1);
	while (str[i])
	{
		if ((str[i] >= 33 && str[i] <= 47) || str[i] == 63 || str[i] == 61
			|| str[i] == 58 || str[i] == '~' || str[i] == ' ' || str[i] == '@')
			return (1);
		i++;
	}
	return (0);
}

int	str_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			return (0);
	}
	return (i);
}

int	arg_is_numeric(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str_is_numeric(str[i]) > 0)
			i++;
		else
			return (0);
	}
	return (i);
}

int	_is_builtin(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (arg)
	{
		if ((len == 4 && ft_strncmp(arg, "echo", 4) == 0) || (len == 9
				&& ft_strncmp(arg, "/bin/echo", 9) == 0))
			return (1);
		else if ((len == 2 && ft_strncmp(arg, "cd", 2) == 0))
			return (1);
		else if ((len == 3 && ft_strncmp(arg, "pwd", 3) == 0)
			|| (len == 8 & ft_strncmp(arg, "/bin/pwd", 8) == 0))
			return (1);
		else if ((len == 6 && ft_strncmp(arg, "export", 6) == 0))
			return (1);
		else if ((len == 5 && ft_strncmp(arg, "unset", 5) == 0))
			return (1);
		else if ((len == 3 && ft_strncmp(arg, "env", 3) == 0) || (len == 8
				&& ft_strncmp(arg, "/bin/env", 8) == 0))
			return (1);
		else if (len == 4 && ft_strncmp(arg, "exit", len) == 0)
			return (1);
	}
	else
		return (0);
}
