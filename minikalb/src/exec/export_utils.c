/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:20:38 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 16:21:21 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	join_var_value_env(t_struct *s, int index, char *new_val)
{
	int		i;
	t_list	*temp_env;
	char	*temp_env1;

	i = 0;
	temp_env = s->env;
	while (i < index)
	{
		temp_env = temp_env->next;
		i++;
	}
	temp_env1 = temp_env->value;
	temp_env->value = ft_strjoin(temp_env1, new_val);
	free(temp_env1);
}

void	join_var_value_exp(t_struct *s, int index, char *new_val)
{
	int		i;
	t_list	*temp_exp;
	char	*temp_exp1;

	i = 0;
	temp_exp = s->export;
	while (i < index)
	{
		temp_exp = temp_exp->next;
		i++;
	}
	temp_exp1 = temp_exp->value;
	if(!temp_exp1)
		temp_exp->value = ft_strdup(new_val);
	else
		temp_exp->value = ft_strjoin(temp_exp1, new_val);
	free(temp_exp1);
}

int	check_identifier(char *args)
{
	int		i;
	char	*before_eq;

	i = 0;
	while (args[i] && args[i] != '=' && args[i] != '+')
		i++;
	if (i == 0)
		return (1);
	before_eq = ft_substr(args, 0, i);
	if (check_digit_special(before_eq) == 1)
	{
		printf("Minishell: export: `%s': not a valid identifier\n", args);
		free(before_eq);
		return (1);
	}
	free(before_eq);
	return (0);
}

int	check_identifier_p(char *args)
{
	int		i;
	char	*before_eq;

	i = 0;
	while (args[i] && args[i] != '=')
		i++;
	before_eq = ft_substr(args, 0, i - 2);
	if (check_digit_special(before_eq) == 1)
	{
		printf("Minishell: export: `%s': not a valid identifier\n", args);
		free(before_eq);
		return (1);
	}
	free(before_eq);
	return (0);
}
