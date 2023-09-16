/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:35:51 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 15:35:53 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	unset_norm(t_struct *s, char **args, int *i, int *exit_stat)
{
	int	check_var_env;
	int	check_var_exp;

	check_var_env = check_existant(args[*i], s->env, 1);
	check_var_exp = check_existant(args[*i], s->export, 1);
	if (check_var_env >= 0)
		delete_node(&s->env, check_var_env);
	if (check_var_exp >= 0)
		delete_node(&s->export, check_var_exp);
	if (check_var_env == 0 && check_var_exp == 0)
		*exit_stat = 1;
	(*i)++;
}

int	unset(t_struct *s, char **args)
{
	int	i;
	int	check_var_env;
	int	check_var_exp;

	i = 0;
	exit_stat = 0;
	while (args[i])
		i++;
	if (i == 1)
		return (exit_stat = 0, 0);
	else
		i = 1;
	while (args[i])
	{
		if (ft_strlen(args[i]) == 1 && ft_strncmp(args[i], "_", 1) == 0)
			i++;
		if (args[i])
			unset_norm(s, args, &i, &exit_stat);
	}
	return (exit_stat);
}
