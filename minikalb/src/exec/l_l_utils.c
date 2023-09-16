/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_l_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:55:01 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 20:59:15 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	ft_lstadd_back(t_list **lst, char *var, char *value)
{
	t_list	*a;
	t_list	*b;

	if (lst == NULL)
		return ;
	a = *lst;
	if (var)
	{
		b = malloc(sizeof(t_list));
		b->var = var;
		b->value = value;
		b->next = NULL;
	}
	if (*lst == NULL)
	{
		*lst = b;
		return ;
	}
	while (a->next)
	{
		a = a->next;
	}
	a->next = b;
}

void	arr_lis_norm(t_list *first_node, char **envp, int *i)
{
	int	eq_index;

	eq_index = search_index(envp[*i], '=');
	if (eq_index != 0)
		ft_lstadd_back(&first_node, ft_substr(envp[*i], 0, eq_index),
			ft_substr(envp[*i], eq_index + 1, ft_strlen(envp[*i]) - eq_index
				+ 1));
	else
		ft_lstadd_back(&first_node, ft_strdup(envp[*i]), NULL);
	(*i)++;
}

t_list	*arr_to_lis(char **envp)
{
	int		i;
	int		eq_index;
	t_list	*first_node;

	i = 1;
	eq_index = search_index(envp[0], '=');
	first_node = malloc(sizeof(t_list));
	if (eq_index != 0)
	{
		first_node->var = ft_substr(envp[0], 0, eq_index);
		first_node->value = ft_substr(envp[0], eq_index + 1, ft_strlen(envp[0])
				- eq_index + 1);
	}
	else
	{
		first_node->var = ft_strdup(envp[0]);
		first_node->value = NULL;
	}
	first_node->next = NULL;
	while (envp[i])
		arr_lis_norm(first_node, envp, &i);
	return (first_node);
}

int	l_l_size(t_list *list)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = list;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

char	**lis_to_arr(t_list *list)
{
	t_list	*temp;
	int		i;
	int		j;
	char	**arr;
	char	*temp_str;

	i = l_l_size(list);
	arr = malloc(sizeof(char *) * (i + 1));
	temp = list;
	j = 0;
	while (j < i)
	{
		temp_str = ft_strjoin(temp->var, "=");
		arr[j] = ft_strjoin(temp_str, temp->value);
		free(temp_str);
		temp = temp->next;
		j++;
	}
	arr[i] = NULL;
	return (arr);
}
