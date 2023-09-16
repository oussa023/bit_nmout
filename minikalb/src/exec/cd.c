/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:16:43 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 17:16:46 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	cd_norm_1(t_struct *s, int oldpwd_index, int pwd_index)
{
	if (oldpwd_index > 0)
	{
		printf("kaka1\n");
		change_val(s, oldpwd_index, get_env_value("PWD", s->env));
	}
	else
	{
		ft_lstadd_back(&s->env, "OLDPWD", get_env_value("PWD", s->env));
		ft_lstadd_back(&s->export, "OLDPWD", get_env_value("PWD", s->env));
	}
	if (pwd_index > 0)
	{
		printf("kaka2\n");
		change_val(s, pwd_index, pwd2());
	}
	else
	{
		ft_lstadd_back(&s->env, "PWD", pwd2());
		ft_lstadd_back(&s->export, "PWD", pwd2());
	}
}

int	cd_norm_1_done(t_struct *s, int index, int oldpwd_index, int pwd_index)
{
	if (index > 0)
	{
		if (chdir(get_env_value("HOME", s->env)) == -1)
			return (exit_stat = 1, 1);
		else
			cd_norm_1(s, oldpwd_index, pwd_index);
	}
	else
		printf("Minishell: cd: HOME not set\n");
}

void	cd_norm_2(t_struct *s, int oldpwd_index, int pwd_index)
{
	if (oldpwd_index > 0)
	{
		printf("kaka3\n");
		change_val(s, oldpwd_index, get_env_value("PWD", s->env));
	}
	else
	{
		ft_lstadd_back(&s->env, "OLDPWD", get_env_value("PWD", s->env));
		ft_lstadd_back(&s->export, "OLDPWD", get_env_value("PWD", s->env));
	}
	if (pwd_index > 0)
	{
		printf("kaka4\n");
		change_val(s, pwd_index, pwd2());
	}
	else
	{
		ft_lstadd_back(&s->env, "PWD", pwd2());
		ft_lstadd_back(&s->export, "PWD", pwd2());
	}
}

int	cd_norm2_done(t_struct *s, char **path, int oldpwd_index, int pwd_index)
{
	if (chdir(path[1]) == -1)
	{
		printf("Minishell: cd: %s: No such file or directory\n", path[1]);
		return (exit_stat = 1, 1);
	}
	else
		cd_norm_2(s, oldpwd_index, pwd_index);
	return (-1);
}

int	cd(char **path, t_struct *s)
{
	int	index;
	int	oldpwd_index;
	int	pwd_index;

	if (get_cmd_length(path) > 2)
	{
		printf("Minishell: cd: too many argumants...\n");
		return (0);
	}
	cd_init(s, &index, &oldpwd_index, &pwd_index);
	if (path[1] == NULL || (ft_strlen(path[1]) == 1 && ft_strncmp(path[1], "~",
				1) == 0) || ft_strlen(path[1]) == 2 && ft_strncmp(path[1], "~/",
			2) == 0)
	{
		if (cd_norm_1_done(s, index, oldpwd_index, pwd_index) != -1)
			return (exit_stat = 1, 1);
	}
	else
	{
		if (cd_norm2_done(s, path, oldpwd_index, pwd_index) != -1)
			return (exit_stat = 1, 1);
	}
	return (exit_stat = 0, 0);
}
