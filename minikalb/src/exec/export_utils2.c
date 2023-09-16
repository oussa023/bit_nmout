/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:18:23 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 16:18:57 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

int	existant_norm(t_list *tmp, int value, int *i, char *args)
{
	int	len;
	int	len2;

	len = ft_strlen(args);
	len2 = ft_strlen(tmp->var);
	if (value == 1)
	{
		if (len == len2 && ft_strncmp(args, tmp->var, len) == 0)
			return (*i);
	}
	else
	{
		if (len == len2 && ft_strncmp(args, tmp->value, len) == 0)
			return (*i);
	}
	(*i)++;
	return (-1);
}

int	check_existant(char *args, t_list *head, int value)
{
	int		i;
	t_list	*tmp;
	int		len;
	int		len2;

	i = 0;
	tmp = head;
	if (!args)
		return (0);
	while (tmp)
	{
		if (existant_norm(tmp, value, &i, args) >= 0)
			return (i);
		tmp = tmp->next;
	}
	return (-1);
}

char	*get_env_value(char *str, t_list *head)
{
	t_list	*temp;

	temp = head;
	while (temp)
	{
		if (ft_strncmp(temp->var, str, ft_strlen(temp->var)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

char	*add_quotes(char *str)
{
	char	*temp;

	temp = ft_strjoin(str, "\"");
	str = temp;
	temp = ft_strjoin("\"", str);
	free(str);
	return (temp);
}

void	export_init2(t_exp *x, t_struct *s, char **cmd)
{
	x->temp_var = ft_substr(cmd[x->i], 0, x->eq_index);
	x->temp_var1 = ft_substr(cmd[x->i], 0, x->eq_index);
	x->temp_value = ft_substr(cmd[x->i], x->eq_index + 1, ft_strlen(cmd[x->i])
			- x->eq_index + 1);
	x->temp_value1 = ft_substr(cmd[x->i], x->eq_index + 1, ft_strlen(cmd[x->i])
			- x->eq_index + 1);
	x->check_var_env = check_existant(x->temp_var, s->env, 1);
	x->check_var_exp = check_existant(x->temp_var, s->export, 1);
	x->check_value_env = check_existant(x->temp_value, s->env, 2);
	x->check_value_exp = check_existant(x->temp_value, s->export, 2);
}
