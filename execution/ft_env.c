/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:43:19 by mobounya          #+#    #+#             */
/*   Updated: 2020/10/19 18:16:46 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/errno.h>
#include <stdio.h>

int		ft_strchri(const char *str, char c);

int		ft_arraysize(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
		i++;
	return (i);
}

char    *ft_getenv(char *var, char **env)
{
	unsigned int    i;
	unsigned int    split_index;
	char            *var_name;
	char            *value;
	unsigned int	len;

	i = 0;
	while (env[i])
	{
		split_index = ft_strchri(env[i], '=');
		var_name = ft_strncpy(ft_strnew(split_index + 1), env[i], split_index);
		if (ft_strcmp(var, var_name) == 0)
		{
			ft_memdel((void**)&var_name);
			len = ft_strlen(env[i] + split_index);
			value = ft_strncpy(ft_strnew(len + 1), env[i] + split_index + 1, len);
			return (value);
		}
		i++;
	}
	return (NULL);
}

char		*ft_get_varname(char *cmd)
{
	unsigned int    split_index;
	char			*var_name;

	split_index = ft_strchri(cmd, '=');
	var_name = ft_strncpy(ft_strnew(split_index + 1), cmd, split_index);
	return (var_name);
}

void		ft_replace_env(char *var_name, char *new_value, char **env)
{
	char	*temp;

	ft_putendl(*env);
	temp = ft_strjoin(var_name, "=");
	*env = ft_strjoin(temp, new_value);
	free(temp);
}

int			ft_find_replace(char *var, char *new_value, char **env)
{
	unsigned int	i;
	unsigned int	sign_index;
	char			*var_name;

	i = 0;
	while (env[i])
	{
		sign_index = ft_strchri(env[i], '=');
		var_name = ft_strncpy(ft_strnew(sign_index + 1), env[i], sign_index);
        if (ft_strcmp(var, var_name) == 0)
		{
			ft_replace_env(var, new_value, (env + i));
            return (0);
		}
		i++;
	}
	return (1);
}

int			ft_append_env(char *var_name, char *value, char ***env)
{
	char	*var_value;
	char	*temp;
	int		size;
	char	**new_env;
	int		i;

	i = 0;
    temp = ft_strjoin(var_name, "=");
	var_value = ft_strjoin(temp, value);
	free(temp);
	size = ft_arraysize(*env);
	if ((new_env = malloc(sizeof(char *) * size + 2)) == NULL)
		exit(ENOMEM);
    while ((*env)[i])
	{
		new_env[i] = ft_strdup((*env)[i]);
		i++;
	}
	new_env[size] = var_value;
	new_env[size + 1] = NULL;
	*env = new_env;
	return (0);
}

int			ft_replace_add_env(char *cmd, char ***env)
{
	char	*var_name;
	char	*value;

	var_name = ft_get_varname(cmd);
	ft_putendl(var_name);
	value = ft_strdup(cmd + ft_strlen(var_name) + 1);
	ft_putendl(value);
	if (ft_find_replace(var_name, value, *env))
        ft_append_env(var_name, value, env);
	return (0);
}