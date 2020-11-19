/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:43:19 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/19 18:56:51 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/errno.h>
#include <stdio.h>

char	*ft_get_varname(char *cmd)
{
	unsigned int	split_index;
	char			*var_name;

	split_index = ft_strchri(cmd, '=');
	var_name = ft_strncpy(ft_strnew(split_index + 1), cmd, split_index);
	return (var_name);
}

void	ft_replace_env(char *var_name, char *new_value, char **env)
{
	char	*temp;

	temp = ft_strjoin(var_name, "=");
	*env = ft_strjoin(temp, new_value);
	free(temp);
}

int		ft_find_replace(char *var, char *new_value, char **env)
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
			ft_memdel((void**)&var_name);
			ft_replace_env(var, new_value, (env + i));
			return (0);
		}
		ft_memdel((void**)&var_name);
		i++;
	}
	return (1);
}

int		ft_append_env(char *var_name, char *value, char ***env)
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
	if ((new_env = malloc(sizeof(char *) * (size + 2))) == NULL)
		exit(ENOMEM);
	while ((*env)[i])
	{
		new_env[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	new_env[size] = var_value;
	new_env[size + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

/*
**	Get the name and value pair (NAME=VALUE), find the right
**	enviroment variable and replace it in the env array, else
**	append it to the end of the list.
*/

int		ft_replace_add_env(char *cmd, char ***env)
{
	char	*var_name;
	char	*value;

	var_name = ft_get_varname(cmd);
	value = ft_strdup(cmd + ft_strlen(var_name) + 1);
	if (ft_find_replace(var_name, value, *env))
		ft_append_env(var_name, value, env);
	ft_memdel((void**)&var_name);
	ft_memdel((void**)&value);
	return (0);
}
