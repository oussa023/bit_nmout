/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:17:14 by okassimi          #+#    #+#             */
/*   Updated: 2023/09/14 19:15:47 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/mini.h"

int exit_stat = 0;

void built_in(t_cmd *cmd, t_struct *s)
{
	int len;

	if (!cmd || cmd->error)
		return;
	len = ft_strlen(cmd->full_cmd[0]);
	if ((len == 4 && ft_strncmp(cmd->full_cmd[0], "echo", 4) == 0) || (len == 9 && ft_strncmp(cmd->full_cmd[0], "/bin/echo", 9) == 0) || (len == 13 && ft_strncmp(cmd->full_cmd[0], "/usr/bin/echo", 13) == 0))
		echo(cmd->full_cmd, cmd->outfile); // done tested
	else if ((len == 2 && ft_strncmp(cmd->full_cmd[0], "cd", 2) == 0))
		cd(cmd->full_cmd, s);
	else if ((len == 3 && ft_strncmp(cmd->full_cmd[0], "pwd", 3) == 0) || (len == 8 && ft_strncmp(cmd->full_cmd[0], "/bin/pwd", 8) == 0) || (len == 12 && ft_strncmp(cmd->full_cmd[0], "/usr/bin/pwd", 12) == 0))
		pwd(cmd);
	else if ((len == 6 && ft_strncmp(cmd->full_cmd[0], "export", 6) == 0))
		export(s, cmd->full_cmd);
	else if ((len == 5 && ft_strncmp(cmd->full_cmd[0], "unset", 5) == 0))
		unset(s, cmd->full_cmd);
	else if ((len == 3 && ft_strncmp(cmd->full_cmd[0], "env", 3) == 0) || (len == 8 && ft_strncmp(cmd->full_cmd[0], "/bin/env", 8) == 0) || (len == 12 && ft_strncmp(cmd->full_cmd[0], "/usr/bin/env", 12) == 0))
		print_env(s->env, cmd);
	else if (len == 4 && ft_strncmp(cmd->full_cmd[0], "exit", ft_strlen(cmd->full_cmd[0])) == 0)
		exit_funct(cmd);
	else
		exec_func(cmd, s, 0);
}

void exc_sig(int sig)
{
	// exit_stat = 130;
	ft_putchar_fd('\n', 1);
	// rl_on_new_line();
	// rl_replace_line("", 1);
	// rl_redisplay();
}

void exc_sig_hanging(int sig)
{
	// exit_stat = 130;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	// exit_sta
}

void	handle_shell_lvl()
{
	int index_exp;//handle shlvl
	int index_env;

	index_exp = check_existant("SHLVL", s->exp, 1);
	index_env = check_existant("SHLVL", s->exp, 1);
	change_val_env(s, index_env, ft_itoa(ft_atoi(get_env_value("SHLVL", env)) + 1))
}
int main(int ac, char **av, char *envp[])
{
	t_cmd *cmd;
	t_struct *s;
	char *buffer;
	signal(SIGQUIT, SIG_IGN);

	s = malloc(sizeof(t_struct));
	int k = 0;
	if (*envp)
	{
		s->env = arr_to_lis(envp);
		s->export = arr_to_lis(envp);
	}
	else
	{
		s->env = NULL;
		s->export = NULL;
		ft_lstadd_back(&s->env, ft_strdup("PATH"), ft_strdup(pwd2()));
		ft_lstadd_back(&s->export, ft_strdup("OLDPWD"), NULL);
		ft_lstadd_back(&s->export, ft_strdup("PATH"), ft_strdup(pwd2()));
	}
	while (1)
	{
		signal(SIGINT, &exc_sig_hanging);
		buffer = readline("Minishell: ");
		if (buffer == NULL)
		{
			write(1, "Exit\n", 5);
			rl_clear_history();
			exit(131);
		}
		add_history(buffer);
		cmd = _parc(buffer, s->env);
		// _print_cmd(cmd);
		if (cmd && *cmd->full_cmd && *cmd->full_cmd[0])
		{
			if (cmd && cmd->next_cmd)
				pipeline(cmd, s);
			else
				built_in(cmd, s);
		}
		// // exit (0);
		_free_cmd(cmd);
		free(buffer);
	}
	free_linked_list(s->env);
	free_linked_list(s->export);
	free(s);
	return (0);
}