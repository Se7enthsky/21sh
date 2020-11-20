/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:41:00 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/20 18:43:54 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	to_remove(char *var_name, char *env_var)
{
	char	*temp;
	int		remove;

	remove = 0;
	temp = ft_get_varname(env_var);
	if (ft_strcmp(var_name, temp) == 0)
		remove = 1;
	free(temp);
	return (remove);
}

static void	ft_fill_env(char **env, char **new_env, char *to_delete)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (to_remove(to_delete, env[i]) == 0)
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
}

int			ft_unsetenv(char **command, char ***env)
{
	char			**new_env;
	size_t			size;

	size = ft_arraysize(command);
	if (size < 2)
	{
		ft_putendl_fd("Usage: unsetenv VAR", 2);
		g_exit_code = 5;
		return (1);
	}
	if (size > 2)
	{
		g_exit_code = 2;
		return (1);
	}
	size = ft_arraysize(*env);
	if ((new_env = malloc(sizeof(char *) * size)) == NULL)
		exit(ENOMEM);
	ft_fill_env(*env, new_env, command[1]);
	free(*env);
	*env = new_env;
	return (0);
}
