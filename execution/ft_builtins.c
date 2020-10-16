/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 13:54:30 by mobounya          #+#    #+#             */
/*   Updated: 2020/10/16 14:46:05 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int		ft_echo(const char **command, char **env)
{
	unsigned int index;

	env = NULL;
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

int			ft_exit(const char **command, char **env)
{
    unsigned int    i;
    int             status;

    i = 0;
    status = 0;
    env = NULL;
    while (command[i])
        i++;
    if (i > 2)
        ft_putendl_fd("exit: too many arguments", 2);
    else if (command[1])
        status = ft_atoi(command[1]);
    exit(status);
    return (0);
}


int			ft_changedir(const char **command, char **env)
{
    unsigned int    size;
    char            *path;

    size = 0;
    while (command[size])
        size++;
    if (size == 1)
        path = ft_get_envalue("HOME", env);
    else if (size > 2)
        ft_putendl_fd("cd: too many arguments", 2);
    else
        path = ft_strdup(command[1]);
    if (path)
	{
		if (access(path, F_OK) != 0)
			ft_putendl_fd("cd: no such file or directory", 2);
		else if (access(path, X_OK) != 0)
			ft_putendl_fd("cd: permission denied", 2);
		else
			chdir(path);
		free(path);
		return (0);
	}
}

int			ft_setenv(const char **command, char **env)
{
    unsigned int    i;

    i = 0;
    while (command[i])
    {
        if (ft_strchr(command[i], '=') == 0)
        {
            ft_putendl_fd("Usage: setenv VARIABLE=VALUE", 2);
            return (1);
        }
        i++;
    }
    return (0);
}

int			ft_unsetenv(const char **command, char **env)
{
    // TODO
    command = NULL;
    return (0);
}

// int			ft_env(char **env)
// {
//     // TODO
//     env == NULL;
// }