/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:06:15 by okassimi          #+#    #+#             */
/*   Updated: 2023/09/13 23:17:02 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

int	_bring_env(char *buffer, int *index, t_node **node)
{
	t_node *tmp;
	int 	i;

	i = 1;
	while (buffer[i] && buffer[i] == ENV)
		i++;
	if (i == 1)
		while (buffer[i] && !_is_special(buffer[i]) && !_is_whitespace(buffer[i]) && !_is_quoted(buffer[i]))
			i++;
	else if ((i % 2) == 1)
		i--;
	(*node)->next_node = malloc(sizeof(t_node));
	(*node)->next_node->sec = ft_substr(buffer, 0, i);
	(*node)->next_node->index = ++(*index);
	(*node)->next_node->genre = GENERAL;
	(*node)->expanded = NULL;
	if (buffer[0] && buffer[0] == ENV && buffer[1] && buffer[1] == ENV)
		(*node)->next_node->type = WORD;
	else
		(*node)->next_node->type = ENV;
	(*node)->next_node->prev_node = (*node);
	(*node) = (*node)->next_node;
	return (i - 1);
}

int	_search_word(char *buffer, int *index, t_node **node)
{
	int i;
	int len;

	i = _count_env(buffer);
	(*node)->next_node = malloc(sizeof(t_node));
	if (i)
		(*node)->next_node->type = ENV;
	else
		(*node)->next_node->type = WORD;
	while (buffer[i] &&!_is_special(buffer[i]) && !_is_whitespace(buffer[i]) && !_is_quoted(buffer[i]))
		i++;
	(*node)->next_node->sec = ft_substr(buffer, 0, i);
	(*node)->next_node->index = ++(*index);
	(*node)->next_node->genre = GENERAL;
	(*node)->expanded = NULL;
	if ((*node)->type == REDIR_INPUT || (*node)->type == REDIR_OUTPUT
		|| (*node)->type == REDIR_APPAND || (*node)->type == REDIR_HERDOC)
		(*node)->next_node->type = DELIMITER;
	if (_search_index((*node)->next_node->sec, '$'))
		(*node)->next_node->type = ENV;
	(*node)->next_node->prev_node = (*node);
	(*node) = (*node)->next_node;
	return (i - 1);
}


int	_put_singl_quote(char *buffer, int *index, t_node **node)
{
	int i;
	
	i = 0;
	(*node)->next_node = malloc(sizeof(t_node));
	(*node)->next_node->sec = ft_strdup("\'");
	(*node)->next_node->index = ++(*index);
	(*node)->next_node->genre = GENERAL;
	(*node)->expanded = NULL;
	(*node)->next_node->type = SINGLE_QUOTE;
	(*node)->next_node->prev_node = (*node);
	(*node) = (*node)->next_node;
	i++;
	while ((*node)->prev_node->genre != IN_S_QUOTE && (buffer[i] && buffer[i] != SINGLE_QUOTE))
		i++;
	if ((*node)->prev_node->genre != IN_S_QUOTE)
	{
		(*node)->next_node = malloc(sizeof(t_node));
		(*node)->next_node->sec = ft_substr(buffer, 1, i - 1);
		(*node)->next_node->index = ++(*index);
		(*node)->next_node->genre = IN_S_QUOTE;
		(*node)->expanded = NULL;
		(*node)->next_node->type = WORD;
		(*node)->next_node->prev_node = (*node);
		(*node) = (*node)->next_node;
	}
	return (i - 1);
}

int	_put_doubl_quote(char *buffer, int *index, t_node **node)
{
	int i;
	
	i = 0;
	(*node)->next_node = malloc(sizeof(t_node));
	(*node)->next_node->sec = ft_strdup("\"");
	(*node)->next_node->index = ++(*index);
	(*node)->next_node->genre = GENERAL;
	(*node)->expanded = NULL;
	(*node)->next_node->type = DOUBLE_QUOTE;
	(*node)->next_node->prev_node = (*node);
	(*node) = (*node)->next_node;
	i++;
	while ((*node)->prev_node->genre != IN_D_QUOTE && (buffer[i] && buffer[i] != DOUBLE_QUOTE))
		i++;
	if ((*node)->prev_node->genre != IN_D_QUOTE)
	{
		(*node)->next_node = malloc(sizeof(t_node));
		(*node)->next_node->sec = ft_substr(buffer, 1, i - 1);
		(*node)->next_node->index = ++(*index);
		(*node)->next_node->genre = IN_D_QUOTE;
		(*node)->expanded = NULL;
		(*node)->next_node->type = WORD;
		(*node)->next_node->prev_node = (*node);
		(*node) = (*node)->next_node;
	}
	return (i - 1);
}

int	_put_in_redir(char *buffer, int *index, t_node **node)
{
	int i;
	
	i = 0;
	(*node)->next_node = malloc(sizeof(t_node));
	(*node)->expanded = NULL;
	if ((buffer[i + 1] == REDIR_INPUT))
	{
		(*node)->next_node->sec = ft_strdup("<<");
		(*node)->next_node->genre = GENERAL;
		(*node)->next_node->type = REDIR_HERDOC;
		i++;
	}
	else
	{
		(*node)->next_node->sec = ft_strdup("<");
		(*node)->next_node->genre = GENERAL;
		(*node)->next_node->type = REDIR_INPUT;
	}
	(*node)->next_node->index = ++(*index);
	(*node)->next_node->prev_node = (*node);
	(*node) = (*node)->next_node;
	return (i);
}

int	_put_out_redir(char *buffer, int *index, t_node **node)
{
	int i;
	
	i = 0;
	(*node)->next_node = malloc(sizeof(t_node));
	(*node)->expanded = NULL;
	if ((buffer[i + 1] == REDIR_OUTPUT))
	{
		(*node)->next_node->sec = ft_strdup(">>");
		(*node)->next_node->genre = GENERAL;
		(*node)->next_node->type = REDIR_APPAND;
		i++;
	}
	else
	{
		(*node)->next_node->sec = ft_strdup(">");
		(*node)->next_node->genre = GENERAL;
		(*node)->next_node->type = REDIR_OUTPUT;
	}
	(*node)->next_node->index = ++(*index);
	(*node)->next_node->prev_node = (*node);
	(*node) = (*node)->next_node;
	return (i);
}

void	_put_pipe_line(char *buffer, int *index, t_node **node)
{
	(*node)->next_node = malloc(sizeof(t_node));
	(*node)->next_node->sec = ft_strdup("|");
	(*index) = 0;
	(*node)->next_node->index = (*index);
	(*node)->next_node->genre = GENERAL;
	(*node)->expanded = NULL;
	(*node)->next_node->type = PIPE_LINE;
	(*node)->next_node->prev_node = (*node);
	(*node) = (*node)->next_node;
}

void	_put_space(char *buffer, int *index, t_node **node)
{
	if ((*index) != 1 && (*node)->type != SPACEE && ((*node)->type == DOUBLE_QUOTE
		|| (*node)->type == SINGLE_QUOTE || (*node)->type == ENV || (buffer[1] && _is_quoted(buffer[1]))))
	{
		(*node)->next_node = malloc(sizeof(t_node));
		(*node)->next_node->sec = ft_strdup(" ");
		(*node)->next_node->index = ++(*index);
		(*node)->next_node->genre = GENERAL;
		(*node)->expanded = NULL;
		(*node)->next_node->type = SPACEE;
		(*node)->next_node->prev_node = (*node);
		(*node) = (*node)->next_node;
	}
}

void	_search_quoted(t_node **lst)
{
	while (*lst)
	{
		if ((*lst)->type == DOUBLE_QUOTE && (*lst)->next_node &&
			((*lst)->next_node->next_node &&
			(*lst)->next_node->next_node->type == DOUBLE_QUOTE))
		{
			if (search_index((*lst)->next_node->sec, ENV))
				(*lst)->next_node->type = ENV;
		}
		else if ((*lst)->type == SINGLE_QUOTE && (*lst)->next_node
			&& ((*lst)->next_node->next_node
			&& (*lst)->next_node->next_node->type == SINGLE_QUOTE))
		{
			if (search_index((*lst)->next_node->sec, ENV))
				(*lst)->next_node->type = ENV;
		}
		*lst = (*lst)->next_node;
	}
}

//echo "$USER" $$'$PATH' > file | cat << limiter > file | cat < file >> out_file
//echo "mama" "lala" "kokok" | echo "mama" "larbi"