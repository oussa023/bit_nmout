/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:47:17 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 15:48:11 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	free_linked_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->var)
			free(tmp->var);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	d_node_free(t_list *temp)
{
	free(temp->var);
	free(temp->value);
	free(temp);
}

void	delete_node(t_list **head, int index)
{
	int		i;
	t_list	*temp;
	t_list	*prev;

	temp = *head;
	i = 0;
	if (*head == NULL)
		return ;
	if (index == 0)
	{
		*head = (*head)->next;
		d_node_free(temp);
		return ;
	}
	while (temp != NULL && i < index)
	{
		prev = temp;
		temp = temp->next;
		i++;
	}
	prev->next = temp->next;
	d_node_free(temp);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
