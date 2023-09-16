/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessible.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:39:12 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 16:39:14 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

char	*cmd_exist_norm(char *temp2, char *temp1, char **path)
{
	if (!access(temp2, F_OK))
	{
		free(temp1);
		free_arr(path);
		return (temp2);
	}
	return (NULL);
}

char	*check_cmd_exist(char *cmd, int i, t_struct *s, char **path)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strdup(cmd);
	if (!access(temp1, X_OK))
	{
		free_arr(path);
		return (temp1);
	}
	free(temp1);
	temp1 = ft_strjoin("/", cmd);
	while (i > 0)
	{
		temp2 = ft_strjoin(path[i], temp1);
		if (cmd_exist_norm(temp2, temp1, path))
			return (temp2);
		free(temp2);
		i--;
	}
	free(temp1);
	free_arr(path);
	return (NULL);
}

char	*accessible(char *cmd, t_struct *s)
{
	int		i;
	int		j;
	t_list	*temp;
	char	**path;

	i = 0;
	if (!cmd || cmd[0] == '\0')
		return (NULL);
	j = check_existant("PATH", s->export, 1);
	temp = s->export;
	if (j > 0)
	{
		while (i < j)
		{
			temp = temp->next;
			i++;
		}
		path = ft_split(temp->value, ':');
		i = path_num(temp->value);
		return (check_cmd_exist(cmd, i, s, path));
	}
	else
		return (NULL);
}

int	path_num(char *path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path[i])
	{
		if (path[i] == ':')
			j++;
		i++;
	}
	return (j);
}

void	cd_init(t_struct *s, int *index, int *oldpwd_index, int *pwd_index)
{
	*index = check_existant("HOME", s->env, 1);
	*oldpwd_index = check_existant("OLDPWD", s->env, 1);
	*pwd_index = check_existant("PWD", s->env, 1);
}
