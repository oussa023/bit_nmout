/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 00:50:21 by okassimi          #+#    #+#             */
/*   Updated: 2023/09/13 22:44:50 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	_put_appand(t_cmd *cmd, t_node *node)
{
	if (cmd->outfile > 2)
		close(cmd->outfile);
	
	cmd->outfile = open(node->next_node->sec, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	if (cmd->outfile == -1)
	{
		cmd->error = strerror(errno);
		if (cmd->error)
			printf("%s\n", cmd->error);
	}
}

void	_put_input(t_cmd *cmd, t_node *node)
{

	cmd->infile = open(node->next_node->sec, O_RDONLY , S_IRWXU);
	if (cmd->infile == -1)
	{
		cmd->error = strerror(errno);
		if (cmd->error)
		{		
			if (node->next_node->expanded && node->next_node->genre == GENERAL)
			{
				printf("minishell: %s: ambiguous redirect\n", node->next_node->expanded);
			}
			else
				printf("minishell: %s: %s\n",node->next_node->sec, cmd->error);
		}
	}
}

void	_put_output(t_cmd *cmd, t_node *node)
{
	if (cmd->outfile > 2)
		close(cmd->outfile);
	cmd->outfile = open(node->next_node->sec, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (cmd->outfile == -1)
	{
		cmd->error = strerror(errno);
		if (cmd->error)
			printf("%s\n", cmd->error);
	}
}