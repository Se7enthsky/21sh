/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:33:00 by mobounya          #+#    #+#             */
/*   Updated: 2020/12/01 02:53:29 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	ft_check_permissions(char *path)
{
	struct stat	s;

	stat(path, &s);
	if (ft_strcmp(path, ".") == 0)
		return (1);
	if (access(path, F_OK) != 0)
		g_exit_code = 1;
	else if (!S_ISDIR(s.st_mode))
		g_exit_code = 4;
	else if (access(path, X_OK) != 0)
		g_exit_code = 3;
	if (g_exit_code)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
	}
	return (g_exit_code);
}

static void	ft_update_oldpwd(char ***env)
{
	char	*var;
	char	*temp;

	var = ft_getenv("PWD", *env);
	if (var)
	{
		temp = var;
		var = ft_strjoin("OLDPWD=", var);
		ft_replace_add_env(var, env);
		ft_memdel((void **)&temp);
		ft_memdel((void **)&var);
	}
}

static void	ft_update_pwd(char ***env)
{
	char	*var;
	char	*temp;

	temp = getcwd(NULL, 0);
	if (temp)
	{
		var = ft_strjoin("PWD=", temp);
		ft_replace_add_env(var, env);
		ft_memdel((void **)&temp);
		ft_memdel((void **)&var);
	}
}

int			ft_changedir(char **command, char ***env)
{
	unsigned int	size;
	char			*path;

	if ((size = ft_arraysize(command)) == 1)
		path = ft_getenv("HOME", *env);
	else if (size > 2)
	{
		g_exit_code = 2;
		return (g_exit_code);
	}
	else if (ft_strcmp(command[1], "-") == 0)
		path = ft_getenv("OLDPWD", *env);
	else
		path = ft_strdup(command[1]);
	if (path && *path)
	{
		if (ft_check_permissions(path) == 0)
		{
			ft_update_oldpwd(env);
			chdir(path);
			ft_update_pwd(env);
		}
		ft_memdel((void **)&path);
	}
	return (g_exit_code);
}
