#ifndef EXECUTE_H
#define EXECUTE_H
#include <sys/types.h>
#include "tokenize.h"

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
 *  Set of functions for piping
 */

void	ft_add_process(t_processes **lst, pid_t pid);
void	ft_lstprocs_wait(t_processes *lst);
int		*ft_create_pipe(void);
int		ft_dupexecute(char **command, int write_end, int read_end);
int		*ft_handle_pipe(t_tokens *lst, int *pipefd, char **command);

#endif