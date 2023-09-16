/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:29:46 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 19:30:10 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	exit_norm(t_cmd *cmd, int arg)
{
	arg = atoi(cmd->full_cmd[1]);
	if (arg >= 0 && arg <= 255)
		exit(atoi(cmd->full_cmd[1]));
	else if (ft_strlen(cmd->full_cmd[1]) == 20 && ft_strncmp(cmd->full_cmd[1],
			"-9223372036854775808", 20) == 0)
		exit(0);
	else if (ft_strlen(cmd->full_cmd[1]) > 20)
	{
		printf("Minishell: exit: %s: numeric argument required",
			cmd->full_cmd[1]);
		exit(2);
	}
	else
		exit(arg % 256);
}

int	exit_funct(t_cmd *cmd)
{
	int	size;
	int	arg;

	size = 0;
	while (cmd->full_cmd[size])
		size++;
	if (size == 1)
		exit(exit_stat);
	else if (size >= 3 && str_is_numeric(cmd->full_cmd[1]) > 0)
	{
		// printf("%s\n", cmd->full_cmd[1]);
		printf("exit\nMinishell: exit: too many arguments\n");
		exit_stat = 1;
	}
	else
	{
		if (str_is_numeric(cmd->full_cmd[1]) > 0)
			exit_norm(cmd, arg);
		else
		{
			printf("Minishell: exit: numeric argument required\n");
			exit(2);
		}
	}
}

int	pwd(t_cmd *cmd)
{
	char	buf[PATH_MAX];
	int		size;

	size = 0;
	while (cmd->full_cmd[size])
		size++;
	if (size == 1)
	{
		getcwd(buf, sizeof(buf));
		printf("%s\n", buf);
		return (exit_stat = 0, 0);
	}
	return (exit_stat = 1, 1);
}

int	ft_lstsize2(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next_cmd;
	}
	return (i);
}
