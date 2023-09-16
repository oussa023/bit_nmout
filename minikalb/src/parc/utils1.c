/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:35:02 by okassimi          #+#    #+#             */
/*   Updated: 2023/09/12 22:02:08 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	print_TokenType(int token)
{
	if (token == SINGLE_QUOTE)
		printf("SINGLE_QUOTE\n");
	else if (token == DELIMITER)
		printf("DELIMITER\n");
	else if (token == ENV)
		printf("ENV\n");
	else if (token == DOUBLE_QUOTE)
		printf("DOUBLE_QUOTE\n");
	else if (token == PIPE_LINE)
		printf("PIPE_LINE\n");
	else if (token == SPACEE)
		printf("SPACE\n");
	else if (token == REDIR_INPUT)
		printf("REDIR_INPUT\n");
	else if (token == REDIR_OUTPUT)
		printf("REDIR_OUTPUT\n");
	else if (token == REDIR_APPAND)
		printf("REDIR_APPAND\n");
	else if (token == REDIR_HERDOC)
		printf("REDIR_HERDOC\n");
	else if (token == WORD)
		printf("WORD\n");
	else 
		printf("wolo\n");
}

void	print_TokenGenre(int token)
{
	if (token == GENERAL)
		printf("GENERAL\n");
	else if (token == IN_D_QUOTE)
		printf("IN_D_QUOTE\n");
	else if (token == IN_S_QUOTE)
		printf("IN_S_QUOTE\n");
}

void	_print_list(t_node *lst)
{
	t_node *tmp;

	tmp = lst;
	if (!lst)
		return ;
	while (tmp)
	{
		// printf("{\n");
		printf("actual : %s\n%d\n", tmp->sec, tmp->index);
		// printf("%p\n", tmp);
		print_TokenType(tmp->type);
		print_TokenGenre(tmp->genre);
		// printf("}\n");
		// if (tmp->index != 1)
		// {
		// 	printf("{\n");
		// 	printf("prev : %s\n%d\n", tmp->prev_node->sec, tmp->prev_node->index);
		// 	// print_TokenType(tmp->prev_node->type);
		// 	// print_TokenGenre(tmp->prev_node->genre);
		// 	printf("}\n");
		// }
		printf("------------------\n");
		tmp = tmp->next_node;
	}
}

//echo "$USER" $$'$PATH' > file | cat << limiter > file | cat < file >> out_file
void	_free_list(t_node *lst, int jeton)
{
	t_node *iter;

	while (lst)
	{
		iter = lst;
		lst = lst->next_node;
		free(iter->sec);
		if (jeton == 0)
		{
			if (iter->expanded)
				free(iter->expanded);
		}
		free(iter);
	}
}

void    _del_node(t_node *node, int index)
{
    int     i;
    t_node  *temp;
    t_node  *temp1;

    temp = node;
    i = 1;
    while (i < index)
    {
        temp1 = temp;
        temp = temp->next_node;
        i++;
    }
    temp1->next_node = temp->next_node;
    free(temp->sec);
    free(temp);
}