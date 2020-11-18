/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:19:28 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/18 13:48:53 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int		ft_setenv(char **command, char ***env)
{
	unsigned int	i;

	i = 1;
	while (command[i])
	{
		if (ft_strchr(command[i], '=') == 0)
		{
			ft_putendl_fd("Usage: setenv VARIABLE=VALUE", 2);
			g_exit_code = 5;
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

int		ft_env(char **cmd, char ***env)
{
	unsigned int	i;

	i = 0;
	cmd = NULL;
	while ((*env)[i])
	{
		ft_putendl((*env)[i]);
		i++;
	}
	return (0);
}

char	*ft_getenv(char *var, char **env)
{
	unsigned int	i;
	unsigned int	split_index;
	char			*var_name;
	char			*value;
	unsigned int	len;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (env[i])
	{
		split_index = ft_strchri(env[i], '=');
		var_name = ft_strncpy(ft_strnew(split_index + 1), env[i], split_index);
		if (ft_strcmp(var, var_name) == 0)
		{
			ft_memdel((void**)&var_name);
			len = ft_strlen(env[i] + split_index);
			value = ft_strncpy(ft_strnew(len + 1), env[i] +
				split_index + 1, len);
			return (value);
		}
		ft_memdel((void**)&var_name);
		i++;
	}
	return (NULL);
}

char	**ft_getpath(char **env)
{
	char	**paths;
	char	*path_value;

	path_value = ft_getenv("PATH", env);
	if (path_value)
	{
		paths = ft_strsplit(path_value, ':');
		free(path_value);
	}
	else
		paths = NULL;
	return (paths);
}
