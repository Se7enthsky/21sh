/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:25:33 by mobounya          #+#    #+#             */
/*   Updated: 2020/10/26 19:30:52 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execute.h"

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
			cmd[index] = string;
			index++;
		}
		else if (list->token_id == WORD)
			cmd[index++] = list->value;
		list = list->next;
	}
	return (cmd);
}

int		is_builtin(char **cmd, char ***env)
{
	uint i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(g_builtin_tab[i].name, cmd[0]))
		{
			g_builtin_tab[i].function(cmd, env);
			return (0);
		}
		i++;
	}
	return (1);
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

int		ft_execbin(t_tokens *lst, char *path, char **args, char **env)
{
	if (access(path, F_OK))
		exit(ENOENT);
	if (access(path, X_OK))
		exit(EACCES);
	if (lst)
		ft_set_redirs(lst);
	if (execve(path, args, env) == -1)
		exit(1);
	return (0);
}

int		ft_run_binary(t_tokens *lst, char *bin, char **args, char **env)
{
	char	**paths;
	char	*temp;
	char	*bin_path;
	uint	i;
	int		pid;
	int		status;

	i = 0;
	paths = ft_getpath(env);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		bin_path = ft_strjoin(temp, bin);
		free(temp);
		pid = fork();
		if (pid == 0)
			ft_execbin(lst, bin_path, args, env);
		else
			waitpid(pid, &status, 0);
		if (status == 2)
		{
			g_exit_code = status;
			break;
		}
		i++;
	}
	return (0);
}

int		ft_run_command(t_tokens *lst, char ***env)
{
	char	**command;

	command = ft_lsttoa(lst);
	if (is_builtin(command, env) == 1)
		ft_run_binary(lst, command[0], command, *env);
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
