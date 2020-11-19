/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:42:39 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/19 18:45:41 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "tokenize.h"
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>

typedef int				t_builtin_function();
int						g_exit_code;
typedef struct			s_builtin_matcher
{
	char				*name;
	t_builtin_function	*function;
}						t_builtin_matcher;

typedef struct			s_processes
{
	pid_t				pid;
	struct s_processes	*next;
}						t_processes;

t_builtin_function		*is_builtin(char **cmd);
int						ft_run_binary(t_tokens *lst, char *bin, char **args,
		char **env);
int						ft_arraysize(char **ar);
void					ft_exec_command(t_tokens *lst, char **command,
		char **env);
int						ft_set_redirs(t_tokens *lst);
void					ft_builtin_exec(t_builtin_function	*builtin,
		t_tokens *lst, char **cmd, char ***env);

/*
**  Set of functions for piping.
*/

void					ft_add_process(t_processes **lst, pid_t pid);
void					ft_lstprocs_wait(t_processes *lst);
int						*ft_create_pipe(void);
int						ft_dupexecute(t_tokens *lst, int write_end,
		int read_end, char ***env);
int						*ft_handle_pipe(t_tokens *lst, int *pipefd,
		char ***env);

/*
**  Function for handling different kinds of redirections, in redirs.c file
**	with other helper functions.
*/

char					*access_bin(char *bin, char **env);
int						ft_set_redirs(t_tokens *lst);

/*
**	Builtin Functions
*/

int						ft_echo(char **command, char ***env);
int						ft_exit(char **command, char ***env);
int						ft_changedir(char **command, char ***env);
int						ft_setenv(char **command, char ***env);
int						ft_unsetenv(char **command, char ***env);
int						ft_env(char **command, char ***env);

/*
**	Functions for dealing with env array.
*/

char					*ft_getenv(char *var, char **env);
char					*ft_get_varname(char *cmd);
void					ft_replace_env(char *var_name, char *new_value,
		char **env);
int						ft_find_replace(char *var, char *new_value, char **env);
int						ft_append_env(char *var_name, char *value, char ***env);
int						ft_replace_add_env(char *cmd, char ***env);
char					**ft_getpath(char **env);

/*
**	Functions for dealing with processes created with pipes.
*/

void					ft_add_process(t_processes **lst, pid_t pid);
void					ft_lstprocs_wait(t_processes *lst);

/*
**	Functions in ft_execute_helpers.c for helping with execution.
*/

char					*ft_find_executable(char *bin, char **env);
void					reset_stds(int save, int reset);
char					**ft_lsttoa(t_tokens *list);
void					ft_reset(int *and_or);

#endif
