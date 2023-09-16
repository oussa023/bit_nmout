/* ******************************************************************** */
/*                                                                      */
/*                                                  :::      ::::::::   */
/*   parc.c                                       :+:      :+:    :+:   */
/*                                              +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>        +#+  +:+       +#+        */
/*                                          +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:32:36 by afaqir      #+#    #+#             */
/*   Updated: 2023/08/20 11:55:25 by afaqir     ###   ########.fr       */
/*                                                                      */
/* ******************************************************************** */

#include "../../incld/mini.h"

int _count_env(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i] && buffer[i] == ENV)
		i++;
	return(i);
}



int	_is_it_option(char *buffer)
{
	int i;
	int jeton;

	i = 0;
	jeton = 0;
	if (buffer[i] == '-' && buffer[i + 1] && buffer[i + 1] == 'n')
	{
		i++;
		while (buffer[i])
		{
			if (buffer[i] != 'n')
			{
				jeton = 1;
				break ;
			}	
			
			i++;
		}
		if (jeton == 1)
			return (0);
		else
			return (1);
	}
	return (0);
}

void	_remove_spaces(t_node *node)
{
	t_node *head;
	t_node *tmp;
	char 	*ptr;
	int 	jeton;

	head = node;
	jeton = 0;
	while (head)
	{
		if (head->next_node &&  head->next_node->type == SPACEE && (!head->next_node->next_node))
		{
			tmp = head->next_node;
			head->next_node = NULL;
			free(tmp->sec);
			free(tmp);
			return ;
		}
		else if (head->next_node && head->next_node->type == SPACEE && (head->next_node->next_node->genre == IN_D_QUOTE || head->next_node->next_node->genre == GENERAL))
		{
			tmp = head->next_node;
			head->next_node = tmp->next_node;
			free(tmp->sec);
			free(tmp);
		}
		else if (head->index != 1 && head->next_node && (head->next_node->genre == IN_D_QUOTE || head->next_node->genre == IN_S_QUOTE))
		{
			tmp = head->next_node;
			head->next_node = tmp->next_node;
			ptr = head->sec;
			head->sec = ft_strjoin(head->sec, tmp->sec);
			free(ptr);
			if (tmp->genre == IN_D_QUOTE)
				head->genre = IN_D_QUOTE;
			else
				head->genre = IN_S_QUOTE;
			free(tmp->sec);
			free(tmp);
			jeton = 1;
		}
		else if (head->index != 1 && head->next_node && ((head->genre == IN_D_QUOTE || head->genre == IN_S_QUOTE) && (head->next_node->genre == GENERAL) && !_is_param(head->next_node) && head->next_node->type != SPACEE))
		{
			// printf("++++++++++>%s\n", head->sec);
			tmp = head->next_node;
			head->next_node = tmp->next_node;
			ptr = head->sec;
			head->sec = ft_strjoin(head->sec, tmp->sec);
			free(ptr);
			if (head->genre == IN_D_QUOTE)
				head->genre = IN_D_QUOTE;
			else 
				head->genre == IN_S_QUOTE;
			free(tmp->sec);
			free(tmp);
			jeton = 1;
		}
		// else if (head->index != 1 && head->next_node && (head->type == ENV && head->next_node->type == ENV))
		// {
		// 	tmp = head->next_node;
		// 	head->next_node = tmp->next_node;
		// 	head->sec = ft_strjoin(head->sec, tmp->sec);
		// 	free(tmp->sec);
		// 	free(tmp);
		// 	jeton = 1;
		// }
		if (jeton == 1)
			jeton = 0;
		else	
			head = head->next_node;
	}
}

void	_visit_linked(t_node *node, t_list *s)
{
	t_node *head;
	t_node *first;
	t_node *tmp;
	int		i;

	head = node;
	first = node;
	i = 0;
	while (head)
	{
		/*this is for the namefile that is between quotes so i remove quotes and consider the string inside quotes is the namefile*/
		if (head->next_node && _is_tquot(head->next_node))
		{
			tmp = head->next_node;
			head->next_node = tmp->next_node;
			free(tmp->sec);
			free(tmp);
		}
		if (head->type == REDIR_HERDOC)
		{
			head = head->next_node;
			head->expanded = NULL;
		}
		else if (head->type == ENV && (head->genre == GENERAL || head->genre == IN_D_QUOTE))
		{
			head->expanded = head->sec;
			// if (head->genre == IN_D_QUOTE)
			// {
			// printf("|%s|\n", head->sec);
			head->sec = _extract_quoted(head->sec, s);
			// }
			// else
			// {
			// 	head->sec = ft_strdup(get_env_value(head->sec + 1, s));
			// 	if (!head->sec)
			// 		head->sec = ft_strdup("");
			// }
		}
		else
			head->expanded = NULL;
		if (head->next_node && _is_tquot(head->next_node))
			i++;
		else
			head = head->next_node;
	}
}

void	_node_init(t_node **head, t_node **node)
{
	*node = malloc(sizeof(t_node));
	*head = *node;
}

t_cmd	*_parc(char *buffer, t_list *s)
{
	t_node *node;
	t_node *fnode;
	t_node *head;
	int i;
	int index;

	_node_init(&head, &node);
	i = 0;
	index = 0;
	while (buffer[i])
	{
		if (!_is_special(buffer[i]) && !_is_whitespace(buffer[i]) && !_is_quoted(buffer[i]))
			i += _search_word(buffer + i, &index, &node);
		else if (buffer[i] == SINGLE_QUOTE)
			i += _put_singl_quote(buffer + i, &index, &node);
		else if (buffer[i] == DOUBLE_QUOTE)
			i += _put_doubl_quote(buffer + i, &index, &node);
		else if (buffer[i] == REDIR_INPUT)
			i += _put_in_redir(buffer + i, &index, &node);
		else if (buffer[i] == REDIR_OUTPUT)
			i += _put_out_redir(buffer + i, &index, &node);
		else if (buffer[i] == PIPE_LINE)
			_put_pipe_line(buffer + i, &index, &node);
		else if (_is_whitespace(buffer[i]))
			_put_space(buffer + i, &index, &node);
		i++;
	}
	node->next_node = NULL;
	fnode = head->next_node;
	if (_get_errors(fnode) == -1)
	{
		_free_list(fnode, 1);
		free(head);
		exit_stat = 2;
		return (0);
	}
	node = head->next_node;
	_search_quoted(&node);
	// _print_list(head->next_node);
	// exit (0);
	_visit_linked(head->next_node, s);
	_remove_spaces(head->next_node);
	// printf("***********************\n");
	// _print_list(head->next_node);
	// exit (0);
	fnode = head->next_node;
	free(head);
	return (_create_cmd(fnode, s));
}


// echo "hoho" "kmokp" 'jj' > "&jj" > "$hoho" > '$hihi'
// lets handle some IN_D_QUOTE sheat