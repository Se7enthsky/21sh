/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:19:28 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/13 18:33:26 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

const t_builtin_matcher	g_builtin_tab[7] =
{
	{"echo", &ft_echo},
	{"exit", &ft_exit},
	{"cd", &ft_changedir},
	{"setenv", &ft_setenv},
	{"unsetenv", &ft_unsetenv},
	{"env", &ft_env},
	{NULL, NULL},
};

int		ft_setenv(char **command, char ***env)
{
	unsigned int	i;

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

int		ft_unsetenv(char **command, char ***env)
{
	char			**new_env;
	size_t			size;
	char			*temp;
	unsigned int	j;

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
		free((*env)[size]);
		free(temp);
		size++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
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

t_builtin_function		*is_builtin(char **cmd)
{
	uint i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(g_builtin_tab[i].name, cmd[0]))
			return (g_builtin_tab[i].function);
		i++;
	}
	return (NULL);
}
