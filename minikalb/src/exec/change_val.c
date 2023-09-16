/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:25:27 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 16:25:28 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	change_val(t_struct *s, int index, char *new_val)
{
	change_val_env(s, index, new_val);
	change_val_exp(s, index, new_val);
}

void	change_val_env(t_struct *s, int index, char *new_val)
{
	int		i;
	int		len;
	t_list	*temp_env;
	char	*temp_env1;

	i = 0;
	len = ft_strlen(new_val);
	temp_env = s->env;
	while (i < index)
	{
		temp_env = temp_env->next;
		i++;
	}
	temp_env1 = temp_env->value;
	if (!(len == ft_strlen(temp_env->value) && ft_strncmp(temp_env->value,
				new_val, len) == 0))
	{
		temp_env->value = ft_strdup(new_val);
		free(temp_env1);
	}
}

void	change_val_exp(t_struct *s, int index, char *new_val)
{
	int		i;
	int		len;
	t_list	*temp_exp;
	char	*temp_exp1;

	i = 0;
	len = ft_strlen(new_val);
	temp_exp = s->export;
	while (i < index)
	{
		temp_exp = temp_exp->next;
		i++;
	}
	temp_exp1 = temp_exp->value;
	if (!(len == ft_strlen(temp_exp->value) && ft_strncmp(temp_exp->value,
				new_val, len) == 0))
	{
		temp_exp->value = ft_strdup(new_val);
		free(temp_exp1);
	}
}
