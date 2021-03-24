/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:33:00 by mobounya          #+#    #+#             */
/*   Updated: 2020/12/01 12:22:16 by awali-al         ###   ########.fr       */
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

static char	*get_path(char **command, char **env)
{
	char	*path;

	path = NULL;
	if (!command[1])
	{
		path = ft_getenv("HOME", env);
		if (!(path))
			ft_putendl_fd("21sh: cd: HOME not set", 2);
	}
	else if (command[2])
	{
		g_exit_code = 2;
		ft_putstr_fd("21sh: cd: ", 2);
	}
	else if (!ft_strcmp(command[1], "-"))
	{
		path = ft_getenv("OLDPWD", env);
		if (!(path))
			ft_putendl_fd("21sh: cd: OLDPWD not set", 2);
	}
	else
		path = ft_strdup(command[1]);
	if (!path && !g_exit_code)
		g_exit_code = 5;
	return (path);
}

int			ft_changedir(char **command, char ***env)
{
	char			*path;

	path = get_path(command, *env);
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
