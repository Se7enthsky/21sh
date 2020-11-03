/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 13:54:30 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/03 01:50:35 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <sys/errno.h>

int		ft_echo(char **command, char ***env)
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

int			ft_exit(char **command, char ***env)
{
    unsigned int    i;
    int             status;

    i = 0;
    status = 0;
    env = NULL;
    while (command[i])
        i++;
    if (i > 2)
    {
        g_exit_code = 2;
        return (g_exit_code);
    }
    else if (command[1])
        status = ft_atoi(command[1]);
    exit(status);
    return (0);
}


int			ft_changedir(char **command, char ***env)
{
    unsigned int    size;
    char            *path;

    size = 0;
    while (command[size])
        size++;
    if (size == 1)
        path = ft_getenv("HOME", *env);
    else if (size > 2)
    {
        ft_memdel((void**)&path);
        g_exit_code = 2;
        return (g_exit_code);
    }
    else
        path = ft_strdup(command[1]);
    if (path && *path)
	{
		if (access(path, F_OK) != 0)
            g_exit_code = 1;
		else if (access(path, X_OK) != 0)
            g_exit_code = 3;
		else
			chdir(path);
		ft_memdel((void**)&path);
	}
    return (g_exit_code);
}

int			ft_setenv(char **command, char ***env)
{
    unsigned int    i;

    i = 1;
    while (command[i])
    {
        if (ft_strchr(command[i], '=') == 0)
        {
            ft_putendl_fd("Usage: setenv VARIABLE=VALUE", 2);
            g_exit_code = 1;
            return (g_exit_code);
        }
        i++;
    }
    i = 1;
    while (command[i])
    {
        ft_replace_add_env(command[i], env);
        i++;
    }
    return (0);
}

int			ft_unsetenv(char **command, char ***env)
{
    char            **new_env;
    size_t          size;
    char            *temp;
    unsigned int    j;

    j = 0;
    size = ft_arraysize(command);
    if (size > 2)
    {
        g_exit_code = 2;
        return (1);
    }
    size = ft_arraysize(*env);
    if ((new_env = malloc(sizeof(char *) * size)) == NULL)
        exit(ENOMEM);
    size = 0;
    while ((*env)[size])
    {
        temp = ft_get_varname((*env)[size]);
        if (ft_strcmp(command[1], temp) != 0)
            new_env[j++] = ft_strdup((*env)[size]);
        free(temp);
        size++;
    }
    new_env[j] = NULL;
    free(*env);
    *env = new_env;
    return (0);
}

int			ft_env(char **cmd, char ***env)
{
    unsigned int    i;

    i = 0;
    cmd = NULL;
    while ((*env)[i])
    {
       ft_putendl((*env)[i]);
       i++;
    }
    return (0);
}