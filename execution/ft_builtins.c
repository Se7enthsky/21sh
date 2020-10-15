#include "execute.h"

int		ft_echo(const char **command)
{
	unsigned int index;

	index = 1;
	while (command[index])
	{
		ft_putstr(command[index]);
		if (command[index + 1])
			ft_putchar_fd(' ', 1);
		index++;
	}
	ft_putchar_fd('\n', 1);
	return (1);
}

int			ft_exit(const char **command)
{
    // TODO
    command = NULL;
    return (0);
}


int			ft_changedir(const char **command)
{
    // TODO
    command = NULL;
    return (0);
}

int			ft_setenv(const char **command)
{
    // TODO
    command = NULL;
    return (0);
}

int			ft_unsetenv(const char **command)
{
    // TODO
    command = NULL;
    return (0);
}

int			ft_env(const char **command)
{
    // TODO
    command = NULL;
    return (0);
}