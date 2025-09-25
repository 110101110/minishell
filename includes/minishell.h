/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:27:37 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/17 22:09:00 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define INVALID 0
# define INPUT 1
# define HEREDOC 2
# define TRUNC 3
# define APPEND 4
# define PIPE 5
# define CMD 6
# define ARG 7
# define SQ 39
# define DQ 34

typedef struct s_command
{
	char				**param;
	int					infile;
	int					outfile;
	int					pid;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_envp
{
	char				*str;
	struct s_envp		*next;
}						t_envp;

typedef struct s_token
{
	char				*str;
	int					type;
	int					quote;
	int					sq;
	int					dq;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_expand_ctx
{
	char				*buf;
	int					i;
	int					j;
}						t_expand_ctx;

typedef struct s_data
{
	t_command			*cmd;
	t_token				*token;
	t_envp				*env;
	int					exit_code;
	int					last_pid;
}						t_data;

extern volatile sig_atomic_t	g_signal_received;
/*parsing*/
char					update_quote(char c, char quote);
int						check_quotes_error(const char *str);
/*tokenisation*/
int						count_tokens(char *line);
t_token					*tokenize_line(char *line);
void					assign_token(t_token *token);
bool					check_syntax(t_data *data, t_token *token);
/*remove & expansion*/
void					token_quote(t_token *token);
bool					expand_and_remove(t_data *data);
bool					remove_quote(t_token *token);
char					*ft_getenv(t_envp *envp, char *var);
bool					append_char(char **dst, int *j, char c);
bool					append_str(char **dst, int *j, char *val);
bool					get_value(char *src, t_expand_ctx *exp, t_data *data);
bool					expansion(t_data *data, t_token *token);
/*command creation*/
bool					create_cmd(t_data *data);
char					**token_arg(t_token *token);
bool					init_cmd(t_data *data);
bool					is_redirect(t_token *token);
bool					init_redirect(t_data *data, t_command *cmd,
							t_token **tok);
bool					handle_heredoc(t_data *data, t_command *cmd,
							t_token **tok);
/*exec*/
bool					exec_cmd(t_data *data, t_command *cmd);
void					child_process(t_data *data, t_command *cmd, int *p_fd,
							int prev_fd);
void					parent_process(t_command *cmd, int *p_fd, int prev_fd);
char					*get_path(char *cmd, t_envp *envp, t_data *data);
bool					cmd_exist(char **path, t_data *data, char *cmd);
void					redirect(t_command *cmd, int *p_fd, int prev_fd);
/*heredoc*/
char					*expand_line(t_data *data, char *line);
bool					write_heredoc(t_data *data, int fd,
							char *line, bool expand);
void					print_eof_warning(char *delim);
bool					handle_heredoc_line(t_data *data, int fd,
							t_token *delim, char *line);
/*signals*/
void					set_signals_prompt(void);
void					set_signals_child(void);
void					set_signal_heredoc(void);
void					set_signals_parent_wait(void);
void					sigquit_ignore(int sig);
void					sigint_heredoc(int sig);
void					sigint_prompt(int sig);
/*builtins*/
bool					is_builtin(char *str);
void					builtin(t_data *data, t_command *cmd, int *p_fd,
							int prev_fd);
bool					launch_builtin(t_data *data, t_command *cmd);
int						ft_echo(char **args);
int						ft_pwd(void);
void					ft_exit(t_data *data, char **args);
int						ft_env(t_envp *envp);
int						ft_export(t_data *data, t_envp **envp, char **args);
int						ft_unset(t_envp **envp, char **args);
int						ft_cd(t_data *data, t_envp **envp, char **args);
/*builtins utils*/
int						count_array(char **args);
void					sort_array(char **arr);
bool					is_valide_id(char *str);
bool					exist_env(t_envp *env, char *str);
int						replace_env(t_data *data, t_envp *env, char *str);
long					ft_atol(const char *str);
/*free utils*/
int						free_envp(t_envp *list);
bool					free_cmd_list(t_command **cmd);
void					free_all(t_data *data, char *error, int exit);
char					**free_array(char **tab);
t_token					*free_token(t_token *token);
bool					free_and_null(char **ptr);
/*utils*/
bool					is_space(char c);
bool					is_quote(char c);
char					**lst_array(t_envp *envp);
int						len_cmd(t_command *cmd);
int						len_envp(t_envp *envp);
char					*copy_str(char *src, int start, int end);
bool					is_var(int c);
int						get_env(t_data *data, char **env);
bool					set_error(t_data *data, const char *msg, int code,
							bool perror_flag);
/*debug*/
void					print_array(char **tab);
void					print_token(t_token *token);
void					debug_print_final_tokens(t_token *head);
void					print_commands(t_command *head);
void					debug_check_fds(t_command *cmd);

#endif
