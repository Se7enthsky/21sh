/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:43:19 by mobounya          #+#    #+#             */
/*   Updated: 2020/10/16 14:48:04 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_get_envalue(char *var, char **env)
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

	temp = ft_strjoin(var_name, "=");
	free(*env);
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

int			ft_replace_add_env(char *cmd, char **env)
{
	char	*var_name;
	char	*value;

	var_name = ft_get_varname(cmd);
	value = "9ete3 new value from command";
	if (ft_find_replace(var_name, value, env))
		ft_append_env_to_array();
	return (0);
}