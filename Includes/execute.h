#ifndef EXECUTE_H
#define EXECUTE_H
#include "tokenize.h"
#include <sys/types.h>
#include <fcntl.h>

typedef int				t_builtin_function();

typedef struct			s_builtin_matcher
{
	char				*name;
	t_builtin_function	*function;
}						t_builtin_matcher;

typedef struct			s_processes
{
	pid_t				pid;
	struct	s_processes *next;
}						t_processes;

int		ft_echo(const char **strings);
int		is_builtin(char	**cmd);
int		ft_run_binary(char *path, char **args, char **env);

/*
 *  Set of functions for piping.
 */

void	ft_add_process(t_processes **lst, pid_t pid);
void	ft_lstprocs_wait(t_processes *lst);
int		*ft_create_pipe(void);
int		ft_dupexecute(t_tokens *lst, int write_end, int read_end);
int		*ft_handle_pipe(t_tokens *lst, int *pipefd);
char	**ft_lsttoa(t_tokens *list);

/*
 *  Function for handling different kinds of redirections, in redirs.c file
 *	with other helper functions.
 */

int		ft_set_redirs(t_tokens *lst);

/*
 *	Builtin Functions
 */

int		ft_echo(const char **command);
int		ft_exit(const char **command);
int		ft_changedir(const char **command);
int		ft_setenv(const char **command);
int		ft_unsetenv(const char **command);
int		ft_env(const char **command);
#endif