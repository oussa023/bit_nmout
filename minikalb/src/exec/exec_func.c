/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:24:16 by omarchic          #+#    #+#             */
/*   Updated: 2023/09/15 19:25:41 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/mini.h"

void	inaccessible(t_cmd *cmd, char **envp_array, char *path)
{
	if (search_index(cmd->full_cmd[0], '/') >= 0)
		printf("Minishell: %s: No such file or directory\n", cmd->full_cmd[0]);
	else
		printf("Minishell: %s: command not found\n", cmd->full_cmd[0]);
	free_arr(envp_array);
	free(path);
}

void	execute(t_cmd *cmd, char *path, char **envp_array)
{
	int	test;

	test = dup(1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2(cmd->infile, 0);
	dup2(cmd->outfile, 1);
	if (execve(path, cmd->full_cmd, envp_array) == -1)
		exit_stat = 1;
	exit(0);
}

void	child_wait(int test)
{
	wait(&test);
	if (WIFEXITED(test))
		exit_stat = WEXITSTATUS(test);
	else if (WIFSIGNALED(test))
		exit_stat = 128 + WTERMSIG(test);
}

void	kill_norm(char **envp_array, char *path, int flag)
{
	if (flag == 1)
	{
		close(0);
		close(1);
	}
	free_arr(envp_array);
	free(path);
}

int	exec_func(t_cmd *cmd, t_struct *s, int flag)
{
	char	**envp_array;
	char	*path;
	int		pid;
	int		test;

	envp_array = lis_to_arr(s->env);
	path = accessible(cmd->full_cmd[0], s);
	if (path == NULL)
	{
		inaccessible(cmd, envp_array, path);
		return (exit_stat = 127, 127);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
		execute(cmd, path, envp_array);
	child_wait(test);
	kill_norm(envp_array, path, flag);
	return (exit_stat);
}
