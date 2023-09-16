/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:18:12 by okassimi          #+#    #+#             */
/*   Updated: 2023/09/14 18:30:10 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
#define MINI_H


# include <sys/wait.h>
# include <wait.h>
# include <stdint.h>
# include <stdint.h>
# include <fcntl.h>
# include "../utils/libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdbool.h>
# include <dirent.h>
# include <linux/limits.h>

/*PARCER STRUCTS*/

extern int exit_stat;
enum TokenGenre {
	GENERAL,
	IN_S_QUOTE,
	IN_D_QUOTE,
};

enum TokenType {
	WORD,
	DELIMITER,
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_INPUT = '<',
	REDIR_OUTPUT = '>',
	SPACEE = '\n',
	DOUBLE_QUOTE = '\"',
	SINGLE_QUOTE = '\'',
	REDIR_APPAND, // >>
	REDIR_HERDOC, // <<
};

typedef struct node {
	char			*sec;
	int				index;
	enum TokenType	type;
	enum TokenGenre	genre;
	char 			*expanded;
	struct node		*next_node;
	struct node		*prev_node;
}	t_node;

typedef struct redir {
	enum TokenType	redir_type;
	char 			*filename;
	struct redir	*next_redir;
}	t_redir;

typedef struct cmd {
	char			**full_cmd;
	int				infile;
	int				outfile;
	char 			*error;
	struct cmd		*next_cmd;
}	t_cmd;

/*EXECUTER STRUCTS*/

typedef struct t_list
{
    char *var;
    char *value;
    struct t_list *next;
} t_list;

typedef struct t_struct
{
    t_list *env;
    t_list *export;
    char **env_arr;

}t_struct;

typedef struct t_exp
{
	int		i;
	int		eq_index;
	int		check_var_env;
	int		check_var_exp;
	int		check_value_env;
	int		check_value_exp;
	char	*temp_var;
	char	*temp_var1;
	char	*temp_value;
	char	*temp_value1;
}			t_exp;
/*PARCER PROTOTYPES*/

t_cmd	*_parc(char *buffer, t_list *s);
int		_get_errors(t_node *lst);

void	_print_list(t_node *lst);
void    _del_node(t_node *node, int index);
void	_free_list(t_node *lst, int jeton);
void	_free_cmd(t_cmd *cmd);
void	print_TokenGenre(int token);
void	print_TokenType(int token);

int	_is_special(char c);
int _is_whitespace(char c);
int	_is_quoted(char c);
int _is_param(t_node *node);

int	_is_what(t_node *node);
int	_is_redir(t_node *node);
t_node	*_count(t_node *node, int *count);
void	_print_cmd(t_cmd *cmd);
int	_is_tquot(t_node *node);
char	*_strjoin(char const *s1, char const *s2);
int	_is_it_option(char *buffer);
int _search_index(const char *s, int c);


int		_bring_env(char *buffer, int *index, t_node **node);
int		_search_word(char *buffer, int *index, t_node **node);
int		_put_singl_quote(char *buffer, int *index, t_node **node);
int		_put_doubl_quote(char *buffer, int *index, t_node **node);
int		_put_in_redir(char *buffer, int *index, t_node **node);
int		_put_out_redir(char *buffer, int *index, t_node **node);
void	_put_space(char *buffer, int *index, t_node **node);
void	_put_pipe_line(char *buffer, int *index, t_node **node);
void	_search_quoted(t_node **lst);

void	_print_error(char *msg);
int		_word_errors(t_node *lst);
int		_input_errors(t_node *lst);
int		_output_errors(t_node *lst);
int		_appand_errors(t_node *lst);
int		_herdoc_errors(t_node *lst);
int		_pipeline_errors(t_node *lst);
int		_singl_q_errors(t_node **lst);
int		_doubl_q_errors(t_node **lst);

int _count_env(char *buffer);
char	*_extract_quoted(char *str,  t_list *env);
char	*_join_char(char *str, char cara);

void	_put_appand(t_cmd *cmd, t_node *node);
void	_put_input(t_cmd *cmd, t_node *node);
void	_put_output(t_cmd *cmd, t_node *node);

t_cmd	*_create_cmd(t_node *node, t_list *s);
void	_visit_linked(t_node *node, t_list *s);
void handle_sig(int);

/*EXECUTER PROTOTYPES*/

char    *pwd2();
int search_index(const char *s, int c);
int echo(char **cmd, int fd);
int     check_existant(char *args, t_list *head, int value);//check if a variable alreadu exists in the environement
int    pwd(t_cmd *cmd);
int    cd(char **path, t_struct *s);
void	ft_lstadd_back(t_list **lst, char *var, char *value);
char    *add_quotes(char *str);
t_list  *arr_to_lis(char **envp);
char    **lis_to_arr(t_list *list);
void    free_arr(char **arr);
int check_digit_special(char *str); //tested;
void    join_var_value_env(t_struct *s, int index, char *new_val);
void    join_var_value_exp(t_struct *s, int index, char *new_val);
int 	check_identifier(char *args);
int 	check_identifier_p(char *args);
void    print_env(t_list *head, t_cmd *cmd);
void    print_export(t_list *head);
void    change_val(t_struct *s, int index, char *new_val);
void    change_val_env(t_struct *s, int index, char *new_val);
void    change_val_exp(t_struct *s, int index, char *new_val);
void    delete_node(t_list **head, int index);
int    unset(t_struct *s, char **args);
int 	export(t_struct *s, char **cmd);
void    free_linked_list(t_list *head);//tested
int 	env(char *envp[]);
int 	path_num(char *path);
char    *check_cmd_exist(char *cmd, int i, t_struct *s, char **path);
char    *accessible(char *cmd, t_struct *s);
void    pipeline(t_cmd *cmd, t_struct *s);
void    pipeline2(char ***cmds, t_struct *s, int ac, char **av);
void    expand(t_struct *s, char *str);
char *get_env_value(char *str, t_list *head);
void    heredoc(t_cmd *cmd, char *delimit, int jeton, t_list *s);
int		exec_func(t_cmd *cmd, t_struct *s, int flag);
void	built_in(t_cmd *cmd, t_struct *s);
void	exc_sig(int sig);
void	exc_sig_hanging(int sig);
void	built_in_pipe(t_cmd *cmd, t_struct *s);
int exit_funct(t_cmd *cmd);
char	*_strjoin(char const *s1, char const *s2);
int		_is_builtin(char *arg);
int     get_cmd_length(char **cmd);
int str_is_numeric(char *str);
void	cd_init(t_struct *s, int *index, int *oldpwd_index, int *pwd_index);
void	export_init2(t_exp *x, t_struct *s, char **cmd);

#endif
//echo "$USER" $$'$PATH' > file | cat << limiter > file | cat < file >> out_file
