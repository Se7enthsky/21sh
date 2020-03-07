#ifndef EXECUTE_H
#define EXECUTE_H

typedef int				t_builtin_function();

typedef struct			s_builtin_matcher
{
	char				*name;
	t_builtin_function	*function;
}						t_builtin_matcher;

int		ft_echo(const char **strings);

#endif