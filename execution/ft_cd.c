/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:33:00 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/30 16:37:47 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static char	*error_message(char *pwd)
{
	ft_putstr_fd(pwd, 2);
	ft_putendl_fd(" is not set", 2);
	return (NULL);
}

static char	*abs_path(char *line)
{
	char		*tmp;
	char		*ret;

	tmp = NULL;
	tmp = ft_strjoin(getcwd(NULL, 0), "/");
	ret = ft_strjoin(tmp, line);
	ft_strdel(&tmp);
	return (ret);
}

static char	*path_correc(char **line, char **env)
{
	char		*pwd;

	if (!line[1])
	{
		pwd = ft_getenv("HOME", env);
		if (!pwd || !pwd[0])
			return (error_message("HOME"));
		else
			return (ft_strdup(pwd));
	}
	else if (!ft_strcmp(line[1], "-"))
	{
		pwd = ft_getenv("OLDPWD", env);
		if (!pwd || !pwd[0])
			return (error_message("OLDPWD"));
		else
			return (ft_strdup(pwd));
	}
	else if (line[1][0] != '/' && ft_strstr(line[1], "./") != line[1]
			&& ft_strstr(line[1], "../") != line[1])
		return (abs_path(line[1]));
	else
		return (ft_strdup(line[1]));
}

static void	check_file(char *tmp)
{
	struct stat	s;

	lstat(tmp, &s);
	if (access(tmp, F_OK))
	{
		g_exit_code = 1;
		ft_putstr_fd("cd: no such file or directory: ", 2);
	}
	else if (!S_ISDIR(s.st_mode))
	{
		g_exit_code = 4;
		ft_putstr_fd("cd: not a directory: ", 2);
	}
	else if (access(tmp, X_OK))
	{
		g_exit_code = 3;
		ft_putstr_fd("cd: permission denied: ", 2);
	}
	ft_putendl_fd(tmp, 2);
}

int			ft_changedir(char **command, char ***env)
{
	char	*tmp;
	int		i;

	i = 0;
	g_exit_code = 0;
	while (command[i])
		i++;
	if (i > 2)
	{
		g_exit_code = 5;
		ft_putendl_fd("cd: too many arguments", 2);
	}
	else if ((tmp = path_correc(command, *env)))
	{
		if (chdir(tmp))
			check_file(tmp);
		else
			change_env_path(env, tmp);
		ft_strdel(&tmp);
	}
	else
		return (1);
	return (0);
}
