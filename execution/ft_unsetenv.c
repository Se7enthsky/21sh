/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:41:00 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/16 14:55:50 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int		to_remove(char *var_name, char *env_var)
{
	char	*temp;
	int		remove;

	remove = 0;
	temp = ft_get_varname(env_var);
	if (ft_strcmp(var_name, temp) == 0)
		remove = 1;
	free(env_var);
	free(temp);
	return (remove);
}

int		ft_unsetenv(char **command, char ***env)
{
	char			**new_env;
	size_t			size;
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
		if (to_remove(command[1], (*env)[size]) == 0)
			new_env[j++] = ft_strdup((*env)[size]);
		size++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}
