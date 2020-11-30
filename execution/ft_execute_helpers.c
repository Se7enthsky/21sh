/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:34:21 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/30 17:16:32 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void		reset_stds(int save, int reset)
{
	static int	stdin_copy;
	static int	stdout_copy;
	static int	stder_copy;

	if (save)
	{
		stdin_copy = dup(0);
		stdout_copy = dup(1);
		stder_copy = dup(2);
	}
	if (reset)
	{
		dup2(stdin_copy, 0);
		dup2(stdout_copy, 1);
		dup2(stder_copy, 2);
		close(stdin_copy);
		close(stdout_copy);
		close(stder_copy);
	}
}

int			ft_permission(char *path_bin)
{
	struct stat	s;

	lstat(path_bin, &s);
	g_exit_code = 0;
	if (access(path_bin, F_OK))
		g_exit_code = 1;
	else if (S_ISDIR(s.st_mode))
	{
		g_exit_code = 5;
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(path_bin, 2);
		ft_putendl_fd(" is a directory", 2);
	}
	else if (access(path_bin, X_OK))
		g_exit_code = 3;
	else
		g_exit_code = 0;
	return (g_exit_code);
}

char		*ft_search_path(char *binary, char **env)
{
	char	**paths;
	uint	i;
	char	*temp;
	char	*path_bin;

	i = 0;
	path_bin = NULL;
	paths = ft_getpath(env);
	if (paths != NULL)
	{
		while (paths[i])
		{
			temp = ft_strjoin(paths[i], "/");
			path_bin = ft_strjoin(temp, binary);
			ft_memdel((void**)&temp);
			if (ft_permission(path_bin) == 0)
				break ;
			ft_memdel((void**)&path_bin);
			i++;
		}
	}
	else
		g_exit_code = 1;
	ft_free_arr(paths);
	return (path_bin);
}

char		*ft_find_executable(char *bin, char **env)
{
	char			*path_bin;

	if (bin && (bin[0] == '/' || ft_strstr(bin, "./") == bin
			|| ft_strstr(bin, "../") == bin))
	{
		if (ft_permission(bin) == 0)
			return (ft_strdup(bin));
		else
			return (NULL);
	}
	else
		path_bin = ft_search_path(bin, env);
	return (path_bin);
}

void		setup_andor(t_ast *root, int *and_or)
{
	if (root->token->token_id == OR)
	{
		and_or[1] = 1;
		if (g_exit_code)
			setup_files(root->right);
	}
	else if (root->token->token_id == AND)
	{
		and_or[0] = 1;
		if (g_exit_code == 0)
			setup_files(root->right);
	}
	else
		setup_files(root->right);
}
