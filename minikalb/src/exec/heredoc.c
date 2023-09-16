#include "../../incld/mini.h"

void	exc_sig_heredoc(int sig)
{
    printf("kolokala\n");
	exit(130);
}

void    heredoc(t_cmd *cmd, char *delimit, int jeton, t_list *s)
{
    if (cmd->infile > 2)
		close(cmd->outfile);
    char *heredoc_buf;
    int len_delimit;
    int pid;
    int status;
    int fd[2];

    if(pipe(fd) == -1)
        return ;
    len_delimit = ft_strlen(delimit);
    pid = fork();
    if(pid == -1)
        return ;
    if(pid == 0)
    {
        while(1)
        {
            signal(SIGINT, &exc_sig_heredoc);
            heredoc_buf = readline(">> ");
            if(!heredoc_buf)
                exit(0);
            if (jeton == 1)
                heredoc_buf = _extract_quoted(heredoc_buf, s);
            if(!heredoc_buf || (ft_strlen(heredoc_buf) == len_delimit && ft_strncmp(delimit, heredoc_buf, len_delimit) == 0))
            {
                free(heredoc_buf);
                exit(0);
            }
            ft_putstr_fd(heredoc_buf, fd[1], 2);
            free(heredoc_buf);
        }
        exit(0);
    }
    wait(&status);
    // printf("%d\n", pid);
    if (WIFEXITED(status))
        exit_stat = WEXITSTATUS(status);
    else if(WIFSIGNALED(status))
		exit_stat = 128 + WTERMSIG(status);
    close(fd[1]);
    // cmd->infile = fd[0];
}