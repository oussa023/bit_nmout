/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:23:09 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 16:23:19 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	print_env(t_list *head, t_cmd *cmd)
{
	t_list	*roll;

	roll = head;
	if (!cmd->full_cmd[1])
	{
		while (roll)
		{
			printf("%s=%s\n", roll->var, roll->value);
			roll = roll->next;
		}
		exit_stat = 0;
	}
	else
	{
		printf("env: %s: No such file or directory\n", cmd->full_cmd[1]);
		exit_stat = 1;
	}
}

void	print_export(t_list *head)
{
	t_list	*roll;

	roll = head;
	while (roll)
	{
		if (roll->value == NULL)
			printf("define -a %s\n", roll->var);
		else
			printf("define -a %s=\"%s\"\n", roll->var, roll->value);
		roll = roll->next;
	}
}

int	get_cmd_length(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}
