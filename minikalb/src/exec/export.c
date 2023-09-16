/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 02:48:14 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/16 02:50:50 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	export_init1(t_exp *x, t_struct *s, char **cmd)
{
	x->temp_var = ft_substr(cmd[x->i], 0, x->eq_index - 1);
	x->temp_var1 = ft_substr(cmd[x->i], 0, x->eq_index - 1);
	x->temp_value = ft_substr(cmd[x->i], x->eq_index + 1, ft_strlen(cmd[x->i])
			- x->eq_index + 1);
	x->temp_value1 = ft_substr(cmd[x->i], x->eq_index + 1, ft_strlen(cmd[x->i])
			- x->eq_index + 1);
	x->check_var_env = check_existant(x->temp_var, s->env, 1);
	x->check_value_env = check_existant(x->temp_value, s->env, 2);
	x->check_var_exp = check_existant(x->temp_var, s->export, 1);
	x->check_value_exp = check_existant(x->temp_value, s->export, 2);
}

void	export_norm(t_exp *x, t_struct *s, char **cmd)
{
	printf("test2\n\n");
	export_init1(x, s, cmd);
	if (x->check_var_env >= 0)
	{
		printf("test2  1\n\n");
		join_var_value_env(s, x->check_var_env, x->temp_value);
		free(x->temp_var);
		free(x->temp_value);
	}
	else
		ft_lstadd_back(&s->env, x->temp_var, x->temp_value);
	if (x->check_var_exp >= 0)
	{
		printf("test2  2\n\n");
        printf("%s\n", x->temp_value1);
		join_var_value_exp(s, x->check_var_exp, x->temp_value1);
		free(x->temp_var1);
		free(x->temp_value1);
	}
	else
		ft_lstadd_back(&s->export, x->temp_var1, x->temp_value1);
}

void	export_norm2(t_exp *x, t_struct *s, char **cmd)
{
	export_init2(x, s, cmd);
	if (x->check_var_env >= 0)
	{
		printf("test3  1\n\n");
		change_val_env(s, x->check_var_env, x->temp_value);
		free(x->temp_var);
		free(x->temp_value);
	}
	else
		ft_lstadd_back(&s->env, x->temp_var, x->temp_value);
	if (x->check_var_exp >= 0)
	{
		printf("test3  2\n\n");
		change_val_exp(s, x->check_var_exp, x->temp_value1);
		free(x->temp_var1);
		free(x->temp_value1);
	}
	else
		ft_lstadd_back(&s->export, x->temp_var1, x->temp_value1);
}

void	export_check(t_exp *x, t_struct *s, char **cmd)
{
	x->eq_index = search_index(cmd[x->i], '=');
	if (x->eq_index == -1)
		x->eq_index = 0;
	if ((x->eq_index == 0) && check_identifier(cmd[x->i]) == 0
		&& check_existant(cmd[x->i], s->export, 1) == -1)
	{
		printf("test1  %s  %d\n", cmd[x->i], check_existant(cmd[x->i],
				s->export, 0));
		ft_lstadd_back(&s->export, ft_strdup(cmd[x->i]), NULL);
	}
	else if (x->eq_index != 0 && cmd[x->i][x->eq_index - 1] == '+'
		&& check_identifier_p(cmd[x->i]) == 0)
    {
        printf("%s\n",cmd[x->i]);
		export_norm(x, s, cmd);
    }
	else if (x->eq_index != 0 && check_identifier(cmd[x->i]) == 0)
		export_norm2(x, s, cmd);
}

int	export(t_struct *s, char **cmd)
{
	t_exp	x;

	x.i = 1;
	if (!cmd[1])
	{
		print_export(s->export);
		return (exit_stat = 0, 0);
	}
	while (cmd[x.i])
	{
		if (cmd[1])
			export_check(&x, s, cmd);
		x.i++;
	}
	return (exit_stat = 0, 0);
}
