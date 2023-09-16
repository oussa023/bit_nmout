/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   U_get_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 02:51:17 by okassimi          #+#    #+#             */
/*   Updated: 2023/09/12 14:24:04 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	_print_error(char *msg)
{
	write(1, "Minishell: ", 11);
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
}

int	_word_errors(t_node *lst)
{
	if (lst->sec && lst->sec[0] == '&')
	{
		_print_error("syntax error near unexpected token `&'");
		return (-1);
	}
}

int	_input_errors(t_node *lst)
{
	lst = lst->next_node;
	if (!lst )
	{
		_print_error("syntax error near unexpected token 'newline'");
		return (-1);
	}
	else if (lst && (lst->type == PIPE_LINE))
	{
		_print_error("syntax error near unexpected token '|'");
		return (-1);
	}
	else if (lst && (lst->type == REDIR_APPAND || lst->type == REDIR_HERDOC
		|| lst->type == REDIR_INPUT || lst->type == REDIR_OUTPUT))
	{
		_print_error("syntax error near unexpected token '>>'");
		return (-1);
	}
}

int	_output_errors(t_node *lst)
{
	lst = lst->next_node;
	if (!lst )
	{
		_print_error("syntax error near unexpected token 'newline'");
		return (-1);
	}
	else if (lst && (lst->type == PIPE_LINE))
	{
		_print_error("syntax error near unexpected token '|'");
		return (-1);
	}
	else if (lst && (lst->type == REDIR_APPAND || lst->type == REDIR_HERDOC
		|| lst->type == REDIR_INPUT || lst->type == REDIR_OUTPUT))
	{
		_print_error("syntax error near unexpected token '>>'");
		return (-1);
	}
}

int	_appand_errors(t_node *lst)
{
	lst = lst->next_node;
	if (!lst )
	{
		_print_error("syntax error near unexpected token 'newline'");
		return (-1);
	}
	else if (lst && (lst->type == PIPE_LINE))
	{
		_print_error("syntax error near unexpected token '|'");
		return (-1);
	}
	else if (lst && (lst->type == REDIR_APPAND || lst->type == REDIR_HERDOC
		|| lst->type == REDIR_INPUT || lst->type == REDIR_OUTPUT))
	{
		_print_error("syntax error near unexpected token '>>'");
		return (-1);
	}
}

int	_herdoc_errors(t_node *lst)
{
	lst = lst->next_node;
	if (!lst )
	{
		_print_error("syntax error near unexpected token 'newline'");
		return (-1);
	}
	else if (lst && (lst->type == PIPE_LINE))
	{
		_print_error("syntax error near unexpected token '|'");
		return (-1);
	}
	else if (lst && (lst->type == REDIR_APPAND || lst->type == REDIR_HERDOC
		|| lst->type == REDIR_INPUT || lst->type == REDIR_OUTPUT))
	{
		_print_error("syntax error near unexpected token '>>'");
		return (-1);
	}
}

int	_pipeline_errors(t_node *lst)
{
	lst = lst->next_node;
	if (!lst )
	{
		_print_error("syntax error near unexpected token 'newline'");
		return (-1);
	}
	else if (lst && (lst->type == PIPE_LINE))
	{
		_print_error("syntax error near unexpected token '|'");
		return (-1);
	}
	// else if (lst && (lst->type == REDIR_APPAND || lst->type == REDIR_HERDOC
	// 	|| lst->type == REDIR_INPUT || lst->type == REDIR_OUTPUT))
	// {
	// 	_print_error("syntax error near unexpected token '>>'");
	// 	return (-1);
	// }
}

int	_singl_q_errors(t_node **lst)
{	
	int jeton;

	jeton = -1;
	(*lst) = (*lst)->next_node;
	if (!(*lst))
	{
		_print_error("Missing single Quote");
		return (-1);
	}
	while (*lst)
	{
		if ((*lst)->type == SINGLE_QUOTE)
		{
			jeton = 0;
			break ;
		}	
		*lst = (*lst)->next_node;
	}
	if (jeton == -1)
	{
		_print_error("Missing Single Quote");
		return (-1);
	}
}

int	_doubl_q_errors(t_node **lst)
{	
	int jeton;

	jeton = -1;
	*lst = (*lst)->next_node;
	if (!(*lst))
	{
		_print_error("Missing Double Quote");
		return (-1);
	}
	while (*lst)
	{
		if ((*lst)->type == DOUBLE_QUOTE)
		{
			jeton = 0;
			break ;
		}
		*lst = (*lst)->next_node;
	}
	if (jeton == -1)
	{
		_print_error("Missing Double Quote");
		return (-1);
	}
}