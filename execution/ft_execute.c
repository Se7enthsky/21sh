/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:25:33 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/03 04:16:48 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execute.h"
#include "errors.h"

t_processes		*g_procs_lst = NULL;

const t_builtin_matcher g_builtin_tab[7] =
{
	{"echo", &ft_echo},
	{"exit", &ft_exit},
	{"cd", &ft_changedir},
	{"setenv", &ft_setenv},
	{"unsetenv", &ft_unsetenv},
	{"env", &ft_env},
	{NULL, NULL},
};

char	**ft_lsttoa(t_tokens *list)
{
	int			size;
	char		**cmd;
	int			index;
	t_tokens	*temp;
	char		*string;

	size = 0;
	index = 0;
	temp = list;
	while (temp)
	{
		if (temp->token_id == WORD || temp->token_id == SQ_STRING \
			|| temp->token_id == DQ_STRING)
			size++;
		temp = temp->next;
	}
	if ((cmd = malloc(sizeof(char *) * (size + 1))) == NULL)
		exit(ENOMEM);
	cmd[size] = NULL;
	while (index < size)
	{
		if (list->token_id == DQ_STRING || list->token_id == SQ_STRING)
		{
			list->value[ft_strlen(list->value) - 1] = '\0';
			string = ft_strdup(list->value + 1);
			free(list->value);
			list->value = string;
			cmd[index] = string;
			index++;
		}
		else if (list->token_id == WORD)
			cmd[index++] = list->value;
		list = list->next;
	}
	return (cmd);
}

t_builtin_function	*is_builtin(char **cmd)
{
	uint i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(g_builtin_tab[i].name, cmd[0]))
			return g_builtin_tab[i].function;
		i++;
	}
	return (NULL);
}

char	**ft_getpath(char **env)
{
	char	**paths;
	char	*path_value;

	path_value = ft_getenv("PATH", env);
	paths = ft_strsplit(path_value, ':');
	free(path_value);
	return (paths);
}

void	reset_stds(int save, int reset)
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

char	*access_bin(char *bin, char **env)
{
	char	**paths;
	char	*temp;
	char	*path_bin;
	int		i;
	int		error;

	i = 0;
	error = 0;
	paths = ft_getpath(env);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path_bin = ft_strjoin(temp, bin);
		free(temp);
		if (access(path_bin, F_OK))
			g_exit_code = 1;
		else if (access(path_bin, X_OK))
		{
			free(path_bin);
			g_exit_code = 3;
			return NULL;
		}
		else
		{
			g_exit_code = 0;
			return (path_bin);
		}
		free(path_bin);
		i++;
	}
	return (NULL);
}
int		ft_run_command(t_tokens *lst, char ***env)
{
	char				**command;
	t_builtin_function	*builtin;
	int					pid;
	char				*path_bin;
	int					status;

	g_exit_code = 0;
	command = ft_lsttoa(lst);
	if ((builtin = is_builtin(command)) == NULL)
	{
		if ((path_bin = access_bin(command[0], *env)))
		{
			if ((pid = fork()) == 0)
			{
				ft_set_redirs(lst);
				execve(path_bin, command, *env);
				exit(1);
			}
			else
				waitpid(pid, &status, 0);
			g_exit_code = status;
		}
		else
		{
			if (g_exit_code == 1)
			{
				ft_putstr_fd("21sh: command not found: ", 2);
				ft_putendl_fd(command[0], 2);
			}
			else if (g_exit_code == 3)
				ft_errors();
		}
	}
	else
	{
		reset_stds(1, 0);
		ft_set_redirs(lst);
		builtin(command, env);
		if (g_exit_code)
			ft_errors();
		reset_stds(0, 1);
	}
	return (0);
}

int		ft_execute_command(t_tokens *lst, char ***env)
{
	static int	*pipefd;

	if (lst->pipe_before || lst->pipe_after)
		pipefd = ft_handle_pipe(lst, pipefd, env);
	else
		ft_run_command(lst->command_tokens, env);
	return (0);
}

int		*ft_execute(t_ast *root, char ***env)
{
	static int		and_or[2] = {-1, -1};

	if (root == NULL)
		return (and_or);
	ft_execute(root->left, env);
	if (root->token->token_id == OR)
		and_or[1] = 1;
	else if (root->token->token_id == AND)
		and_or[0] = 1;
	if (root->token->token_id == SIMPLE_COMMAND)
	{
		if ((and_or[0] == -1 && and_or[1] == -1) || \
			((and_or[1] == 1 && g_exit_code != 0) \
				|| (and_or[0] == 1 && g_exit_code == 0)))
		{
			ft_execute_command(root->token, env);
			and_or[0] = -1;
			and_or[1] = -1;
		}
	}
	ft_execute(root->right, env);
	return (and_or);
}
