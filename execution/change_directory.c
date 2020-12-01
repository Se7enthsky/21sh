/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 21:58:12 by awali-al          #+#    #+#             */
/*   Updated: 2020/12/01 02:24:44 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char		*par_fol(void)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	tmp = ft_strrchr(cwd, '/');
	if (tmp && tmp != cwd)
		return (ft_strndup(cwd, tmp - cwd));
	else if (tmp && tmp == cwd)
		return (ft_strdup("/"));
	else
		return (NULL);
}

static void	bigger_env(char ***env, char *var, int i, int n)
{
	char	**tmp;

	tmp = *env;
	*env = (char**)malloc((n + i + 1) * sizeof(char*));
	n = 0;
	while (tmp[n])
	{
		(*env)[n] = ft_strdup(tmp[n]);
		ft_strdel(&tmp[n]);
		n++;
	}
	free(tmp);
	if (i == 1)
	{
		(*env)[n] = ft_strdup(var);
		n++;
	}
	else
	{
		(*env)[n] = ft_strdup("OLDPWD=");
		(*env)[n + 1] = ft_strdup("PWD=");
		n += 2;
	}
	(*env)[n] = NULL;
}

static void	fixing_env(char ***env)
{
	char	*var;
	int		n;
	int		i;

	i = 2;
	n = 0;
	while ((*env)[n])
	{
		if (ft_strstr((*env)[n], "PWD=") == (*env)[n])
		{
			var = "OLDPWD=";
			i--;
		}
		else if (ft_strstr((*env)[n], "OLDPWD=") == (*env)[n])
		{
			var = "PWD=";
			i--;
		}
		n++;
	}
	if (i)
		bigger_env(env, var, i, n);
}

void		change_env_path(char ***env, char *cwd)
{
	int		p;
	int		o;

	fixing_env(env);
	if (ft_strstr(cwd, "../") == cwd &&
		ft_strlen(cwd) >= 5 && cwd[3] == '.' &&
			(cwd[4] == '/' || cwd[4] == '.'))
	{
		free(cwd);
		cwd = ft_strdup(getcwd(NULL, 0));
	}
	p = 0;
	while (ft_strstr((*env)[p], "PWD=") != (*env)[p])
		p++;
	o = 0;
	while (ft_strstr((*env)[o], "OLDPWD=") != (*env)[o])
		o++;
	ft_strdel(&(*env)[o]);
	(*env)[o] = ft_strjoin("OLD", (*env)[p]);
	ft_strdel(&(*env)[p]);
	(*env)[p] = ft_strjoin("PWD=", cwd);
}
