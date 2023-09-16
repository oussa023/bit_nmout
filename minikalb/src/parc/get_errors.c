/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 02:41:21 by okassimi          #+#    #+#             */
/*   Updated: 2023/08/30 20:11:16 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

int	_get_errors(t_node *lst)
{
	t_node	*head;
	int		error_check;
	int		jeton;

	head = lst;
	error_check = 0;
	jeton = 0;
	while (head)
	{
		// if (head->type == WORD)
		// 	error_check = _word_errors(head);
		if (head->type == REDIR_INPUT)
			error_check = _input_errors(head);
		else if (head->type == REDIR_OUTPUT)
			error_check = _output_errors(head);
		else if (head->type == REDIR_APPAND)
			error_check = _appand_errors(head);
		else if (head->type == REDIR_HERDOC)
			error_check = _herdoc_errors(head);
		else if (head->type == PIPE_LINE)
			error_check = _pipeline_errors(head);
		else if (head->type == SINGLE_QUOTE)
			error_check = _singl_q_errors(&head);
		else if (head->type == DOUBLE_QUOTE)		
			error_check = _doubl_q_errors(&head);
		if (error_check == -1)
			return (-1);
		head = head->next_node;
	}
}
