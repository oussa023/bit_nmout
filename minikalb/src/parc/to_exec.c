/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 03:11:13 by okassimi          #+#    #+#             */
/*   Updated: 2023/09/14 18:31:48 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

int	_is_what(t_node *node)
{
	if (node->type == REDIR_INPUT ||node->type == REDIR_APPAND
		|| node->type == REDIR_HERDOC || node->type == REDIR_OUTPUT || node->type == SINGLE_QUOTE
			|| node->type == DOUBLE_QUOTE || node->type == DELIMITER)
		return (1);
	return (0);
}

int	_is_redir(t_node *node)
{
	if (node)
	{
		if (node->type == REDIR_INPUT)
			return (REDIR_INPUT);
		else if (node->type == REDIR_HERDOC)
			return (REDIR_HERDOC);
		else if  (node->type == REDIR_OUTPUT)
			return (REDIR_OUTPUT);
		else if (node->type == REDIR_APPAND)
			return (REDIR_APPAND);
	}
	return (0);
}

t_node	*_count(t_node *node, int *count)
{
	t_node *tmp;
	t_node *prev;

	tmp = node;
	prev = node;
	while (tmp && tmp->type != PIPE_LINE)
	{
		if (!_is_redir(prev) && !_is_what(tmp))
			(*count)++;
		prev = tmp;
		tmp = tmp->next_node;
	}	//	printf("tmp->type:
	return (tmp);
}
//    ls -la hello world | mam gahada | aji ngoool liik nmchi ewand a| wa ta siiir rah | mamam
//echo "$USER" $$'$PATH' > file | cat << limiter > file | cat < file >> out_file

void	_print_cmd(t_cmd *cmd)
{
	int i;
	t_cmd *tmp;
	t_cmd *head;
	t_redir *fst;

	i = 0;
	tmp = cmd;
	head = cmd;
	while (tmp)
	{
		while (tmp->full_cmd[i])
		{
			printf("|%s|\n", tmp->full_cmd[i]);
			i++;
		}
		i = 0;
		printf("{\n");
		printf("%d\n", tmp->infile);
		printf("%d\n", tmp->outfile);
		// fst = head->redir;
		// while (fst)
		// {
		// 	print_TokenType(fst->redir_type);
		// 	printf("%s\n", fst->filename);
		// 	if (head->redir->redir_type == REDIR_OUTPUT)
		// 	{
		// 		head->outfile = open(tmp->redir->filename, O_CREAT | O_RDWR, S_IRWXU);
		// 	}
		// 	else if (head->redir->redir_type == REDIR_APPAND)
		// 	{
		// 		head->infile = -1;
		// 		head->outfile = open(tmp->redir->filename, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
		// 	}
		// 	else if (head->redir->redir_type == REDIR_INPUT)
		// 	{
		// 		head->infile = open(tmp->redir->filename, O_RDONLY, S_IRUSR);
		// 		head->outfile = -1;
		// 	}
		// 	// else
		// 	// {
		// 	// 	print_TokenType(head->redir->redir_type);
		// 	// 	printf("|%s|\n", tmp->redir->filename);
		// 	// }
		// 	// printf("infile  : %d\n", head->infile);
		// 	// printf("outfile : %d\n", head->outfile);
		// 	fst = fst->next_redir;
		// }
		printf("}\n");
		tmp = tmp->next_cmd;
		head = tmp;
		printf("************************************************************************\n");
	}
}

int	_is_tquot(t_node *node)
{
	if (node->type == SINGLE_QUOTE || node->type == DOUBLE_QUOTE)
		return (1);
	return (0);	// _print_cmd(head->next_cmd);
}

void	_fill_cmd(t_cmd **cmd, t_node *node, int cmdlen, t_list *s)
{

	int	i;
	t_node *tmp;
	t_redir *head;
	
	i = 0;
	tmp = node;
	(*cmd)->next_cmd = malloc(sizeof(t_cmd));
	(*cmd)->next_cmd->full_cmd = malloc((cmdlen + 1) *sizeof(char *));
	while (i < cmdlen)
	{
		
		if (tmp && _is_redir(tmp))
			tmp = tmp->next_node->next_node;
		if (tmp && !_is_tquot(tmp) && !_is_redir(tmp) && tmp->type != DELIMITER)
		{
			if (!tmp->sec)
				(*cmd)->next_cmd->full_cmd[i] = ft_strdup("");
			else
			{
				int	len = ft_strlen(tmp->sec);
				(*cmd)->next_cmd->full_cmd[i] = malloc((len + 1) * sizeof(char));
				(*cmd)->next_cmd->full_cmd[i][len] = 0;
				(*cmd)->next_cmd->full_cmd[i] = strcpy((*cmd)->next_cmd->full_cmd[i], tmp->sec);
			}
			i++;
		}
		tmp = tmp->next_node;
	}
	(*cmd)->next_cmd->infile = 0;
	(*cmd)->next_cmd->outfile = 1;
	(*cmd)->next_cmd->error = NULL;
	(*cmd)->next_cmd->full_cmd[cmdlen] = NULL;
	(*cmd) = (*cmd)->next_cmd;
	/*-----------------------------------------------------------------------------------------------------------------*/
	tmp = node;
	i = 0;
	while (tmp && tmp->type != PIPE_LINE)
	{
		if (_is_redir(tmp) && !(*cmd)->error)
		{
			if (tmp->type == REDIR_APPAND)
				_put_appand((*cmd), tmp);
			else if (tmp->type == REDIR_HERDOC)
			{
				if (tmp->next_node->genre == GENERAL)
					i = 1;
				heredoc((*cmd) , tmp->next_node->sec, i, s);
			}
			else if (tmp->type == REDIR_INPUT)
				_put_input((*cmd), tmp);
			else if (tmp->type == REDIR_OUTPUT)
				_put_output((*cmd), tmp);
		}
		tmp = tmp->next_node;
	}
}

void	_free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp1;
	t_redir *tmp2;
	int		i;
	int		j;

	tmp1 = cmd;
	i = 0;
	j = 0;
	while (cmd)
	{
		while (cmd->full_cmd[i])
		{
			// printf("|%s|\n", cmd->full_cmd[i]);
			free(cmd->full_cmd[i]);
			i++;
		}
		if (cmd->infile > 2)
			close(cmd->infile);
		if (cmd->outfile > 2)
			close(cmd->outfile);
		free(cmd->full_cmd);
		tmp1 = cmd;
		cmd = cmd->next_cmd;
		free(tmp1);
		i = 0;
	}
}


t_cmd	*_create_cmd(t_node *node, t_list *s)
{
	t_node *tmp;
	t_node *iter;
	t_cmd *cmd;
	t_cmd *head;
	int		i;

	tmp = node;
	iter = node;
	i = 0;
	cmd = malloc(sizeof(t_cmd));
	head = cmd;
	while (tmp)
	{
		tmp = _count(tmp, &i);
		_fill_cmd(&cmd, iter, i, s);
		i = 0;
		if (tmp)
		{
			tmp = tmp->next_node;
			iter = tmp;
		}
	}
	cmd->next_cmd = NULL;
	_free_list(node, 0);
	cmd = head->next_cmd;
	free(head);
	return (cmd);
}
