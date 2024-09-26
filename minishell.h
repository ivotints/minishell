/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:48:44 by ivotints          #+#    #+#             */
/*   Updated: 2024/09/26 18:37:13 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//\001 and \002 are used to indicate to Readline where the
//non-printable sequences start and end

// Prompt colors

# define GREEN	"\001\e[1;32m\002"
# define RED	"\001\e[1;31m\002"
# define RESET	"\001\e[0m\002"

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILED 0
# define PATH_MAX	4096
# define LLONG_MAX 9223372036854775807
# define NO_REDIRECT -1

//errors

# define INTERRUPT 128
# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126
# define NOT_EXECUTABLE 126
# define OUT_OF_RANGE 255
# define BUILTIN_MISUSE 2
# define FORK_ERROR -1
# define CMD_NOT_FOUND_MSG	"command not found"
# define NOT_EXECUTABLE_MSG "Is a directory"

//executes

# define IN 0
# define OUT 1

# include "libft/libft.h" // libft
# include <stdio.h> // perror
# include <readline/readline.h> // readline
# include <readline/history.h> // history
# include <stdlib.h> // getenv
# include <unistd.h> // environ, getpwd
# include <sys/wait.h> // waitpid
# include <sys/stat.h> // stat
# include <signal.h> // sigaction
# include <fcntl.h> // open flags

typedef struct s_env
{
	char			*key_pair;
	struct s_env	*next;
}	t_env;

// 01init_minienv.c

t_env	*init_minienv(char **environ);
void	minienv_add(char *key_pair, t_env **minienv);
char	*minienv_value(char *name, t_env *minienv);
char	*value_only(char *key_pair);
t_env	*minienv_node(char *name, t_env *minienv);

// 02minishell.c

int		minishell(t_env *minienv);

// 03signal_handler.c

void	signal_handler(void);

// 04prompt_input.c

char	*prompt_input(t_env *minienv);

// 05free_minienv.c

void	free_minienv(t_env **minienv);
void	close_all_fds(void);
void	close_extra_fds(void);
void	print_perror_msg(char *command, char *perror_msg);

// 06trim_spaces.c

char	*trim_spaces(char *input);
char	*trim_spaces_no_free(char *input);
void	free_array(char **av);

// 07input_error.c

int		input_error(char *input, int *exit_status, t_env *minienv);
int		unclosed_quotes(char *input);
int		pipe_start(char *input);
int		syntax_error(char *token);

// 08redirect_error.c

int		redirect_error(char *input);
int		unexpected_token(char *input);
char	*get_rposition(char *str);
char	*skip_quotes(char *str);

// 09empty_pipe.c

int		empty_pipe(char *input);
char	*get_next_pipe(char *str);

// 10heredoc_handler.c

int		heredoc_handler(char *input, int *exit_status, t_env *minienv);
char	*get_heredoc_pos(char *str);
char	*get_delimiter(char *delim_pos);
void	delete_char(char *str, int len);
int		delimiter_len(char *s);

// 11exec_heredoc.c

int		exec_heredoc(char *delimiter, int *exit_status,
			t_env *minienv, char *input);
void	define_heredoc_signals(int child_pid);
int		wait_for_child(int child_pid, int is_last_child);
int		handle_signal_interrupt(int status, int is_last_child);

// 12read_heredoc.c

void	read_heredoc(int *exit_status, t_env *minienv, char *delimiter);
void	expand_heredoc(char **input, int exit_status, t_env *minienv);
char	*var_position(char *s);
void	insert_string(char **input, char *var_value, char *rest_str);

// 13expand_input.c

void	expand_input(char **input, t_env *minienv, int exit_status);

// 14has_pipe.c

int		has_pipe(char *str);

// 15one_command.c

int		one_command(char *input, t_env **minienv);

// 16handle_redirects.c

int		handle_redirects(char *input, int original_fds[2]);
void	restore_original_fds(int original_fds[2]);

// 17handle_input.c

int		handle_input(char *input, int original_fds[2]);
void	save_original_fd_in(int original_fds[2]);
int		redirect_input(char *input);
char	*get_redirect_position(char *str, char redirect_char);
void	redirect_fd(int fd_to_redirect, int fd_location);

// 18handle_output.c

int		handle_output(char *command, int original_fds[2]);
void	save_original_fd_out(int original_fds[2]);
int		redirect_output(char *command);

// 19redirect_heredoc.c

void	redirect_heredoc(char *command);

// 20split_av.c

char	**split_av(char *input);

// 21is_builtin.c

int		is_builtin(char *cmd);
int		execute_builtin(char **av, t_env **minienv);
int		equal(char *str1, char *str2);

// 22echo.c

int		echo(char **av);

// 23pwd.c

int		pwd(void);

// 24env.c

int		env(t_env *minienv);

// 25builtin_export.c

int		builtin_export(char **av, t_env **minienv);
char	*name_only(char *key_pair);
int		is_valid_varname(char *name);
void	print_varname_error_msg(char *command, char *varname);

// 26minienv_update.c

void	minienv_update(char *name, char *value, t_env *minienv);
char	*create_keypair(char *name, char *value);

// 27unset.c

int		unset(char **av, t_env **minienv);

// 28cd.c

int		cd(char **av, t_env *minienv);

// 29builtin_exit.c

int		builtin_exit(char **args, t_env **minienv);
void	exit_with_error(char *command, char *msg, int error);

// 30exec_fork_extern.c

int		exec_fork_extern(char **av, t_env *minienv);
void	define_execute_signals(int child_pid);

// 31execute_external.c

void	execute_external(char **av, t_env *minienv);
int		is_empty(char *str);
void	external_exit(char **av, t_env *minienv, int exit_status);

// 32getpath.c

char	*get_path(char *command, t_env *minienv);

// 33minienv_to_envp.c

char	**minienv_to_envp(t_env *minienv);
int		minienv_size(t_env *minienv);

// 34split_commands.c

char	**split_commands(char *input);

// 35multiple_commands.c

int		multiple_commands(char **commands, t_env **minienv);
int		*init_children_pid(char **commands);
int		arr_len(char **arr);

// 36handle_pipe.c

void	handle_pipe(int original_fd_out, char *curr_cmd, char **commands);

// 37handle_child_redir.c

void	handle_child_redir(char *command, char **commands, t_env **minienv);
void	quit_child(char **commands, t_env **minienv);

// 38execute_fork_cmd.c

void	execute_fork_cmd(char *command, char **commands, t_env **minienv);
int		execute_forked_builtin(char **args, t_env **minienv);

// 39print_error_msg.c

void	print_error_msg(char *command, char *msg);

// 40wait_for_children.c

int		wait_for_children(int children_pid[1024]);

//try to put it into bash and in to minishell.
//e'cho'  'df""' "$SHE""LL"  "$SHE" "LL|" '$SHELL'|'cat'>$VTE_VERSION
//e'cho'  'df""' "$SHE""LL"  "$SHE" "LL|" '$SHELL'|'cat'>$VT

//echo 1|' '| cat
//echo 1|

//echo "123|'|" | 'cat'

#endif
