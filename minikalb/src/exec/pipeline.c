/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:31:54 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 20:31:56 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	wait_last(int pid, int status)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_stat = 128 + WTERMSIG(status);
}

void	middle_cmds(t_cmd *cmd, t_struct *s, int (*fd)[2], char *path)
{
	int	original;

	original = dup(1);
	close((*fd)[0]);
	dup2((*fd)[1], 1);
	close((*fd)[1]);
	if (_is_builtin(cmd->full_cmd[0]) == 1)
	{
		ft_putstr_fd(cmd->full_cmd[0], original, 1);
		built_in(cmd, s);
	}
	else
	{
		path = accessible(cmd->full_cmd[0], s);
		if (path == NULL)
		{
			ft_putstr_fd("minishell:", original, 1);
			ft_putstr_fd(cmd->full_cmd[0], original, 0);
			ft_putstr_fd(": command not found", original, 2);
		}
		else
			exec_func(cmd, s, 1);
	}
	exit(0);
}

void	last_cmd(t_cmd *cmd, t_struct *s, int original)
{
	char	*path;

	if (_is_builtin(cmd->full_cmd[0]) == 1)
		built_in(cmd, s);
	else
	{
		path = accessible(cmd->full_cmd[0], s);
		if (path == NULL)
		{
			ft_putstr_fd("minishell:", original, 1);
			ft_putstr_fd(cmd->full_cmd[0], original, 0);
			ft_putstr_fd(": command not found", original, 2);
		}
		else
		{
			free(path);
			exec_func(cmd, s, 1);
		}
	}
	while (wait(NULL) != -1)
		continue ;
}

int	pipe_norm(t_cmd *cmd, t_struct *s, int (*fd)[2])
{
	int		pid2;
	char	*path;

	if (pipe(*fd) == -1)
		return (-1);
	pid2 = fork();
	if (pid2 == -1)
	{
		close((*fd)[0]);
		close((*fd)[1]);
		return (-1);
	}
	else if (pid2 == 0)
		middle_cmds(cmd, s, fd, path);
	dup2((*fd)[0], 0);
	close((*fd)[0]);
	close((*fd)[1]);
}

void	pipeline(t_cmd *cmd, t_struct *s)
{
	int	pid;
	int	pid2;
	int	original;
	int	fd[2];
	int	status;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		while (cmd->next_cmd)
		{
			if (pipe_norm(cmd, s, &fd) == -1)
				return ;
			cmd = cmd->next_cmd;
		}
		last_cmd(cmd, s, original);
		exit(0);
	}
	wait_last(pid, status);
}
