#ifndef EXECUTE_H
#define EXECUTE_H

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

#endif