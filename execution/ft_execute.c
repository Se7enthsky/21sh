/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:25:33 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/13 19:49:24 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execute.h"
#include "errors.h"

t_processes	*g_procs_lst = NULL;

char		*ft_remove_quote(char *value)
{
	char	*string;

	value[ft_strlen(value) - 1] = '\0';
	string = ft_strdup(value + 1);
	return (string);
}

void		fill_array(t_tokens *list, char **command)
{
	uint	index;
	char	*string;

	index = 0;
	while (list)
	{
		if (list->token_id == DQ_STRING || list->token_id == SQ_STRING)
		{
			string = ft_remove_quote(list->value);
			free(list->value);
			list->value = string;
			command[index] = string;
			index++;
		}
		else if (list->token_id == WORD)
			command[index++] = list->value;
		list = list->next;
	}
}

char		**ft_lsttoa(t_tokens *list)
{
	int			size;
	char		**cmd;
	t_tokens	*temp;

	size = 0;
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
	fill_array(list, cmd);
	return (cmd);
}

char		**ft_getpath(char **env)
{
	char	**paths;
	char	*path_value;

	path_value = ft_getenv("PATH", env);
	if (path_value)
	{
		paths = ft_strsplit(path_value, ':');
		free(path_value);
	}
	else
		paths = NULL;
	return (paths);
}

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
	g_exit_code = 0;
	if (access(path_bin, F_OK))
		g_exit_code = 1;
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
	if ((paths = ft_getpath(env)) != NULL)
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
	char	*path_bin;

	if (bin && (*bin == '.' || *bin == '/'))
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

void		ft_exec_command(t_tokens *lst, char **command, char **env)
{
	char	*executable;

	ft_set_redirs(lst);
	if (g_exit_code)
		ft_errors();
	else if ((executable = ft_find_executable(command[0], env)))
	{
		execve(executable, command, env);
		exit(1);
	}
	else
	{
		if ((command[0][0] != '.' && command[0][0] != '/') && g_exit_code == 1)
		{
			ft_putstr_fd("21sh: command not found: ", 2);
			ft_putendl_fd(command[0], 2);
		}
		else if (g_exit_code > 0)
			ft_errors();
	}
}

void		ft_bin_exec(t_tokens *lst, char **cmd, char **env)
{
	int		pid;

	if ((pid = fork()) == 0)
	{
		ft_exec_command(lst, cmd, env);
		exit(g_exit_code);
	}
	else
		waitpid(pid, &g_exit_code, 0);
}

void		ft_builtin_exec(t_builtin_function *builtin, t_tokens *lst, char **cmd, char ***env)
{
	reset_stds(1, 0);
	ft_set_redirs(lst);
	if (g_exit_code)
		ft_errors();
	else
	{
		builtin(cmd, env);
		if (g_exit_code)
			ft_errors();
	}
	reset_stds(0, 1);
}

int			ft_run_command(t_tokens *lst, char ***env)
{
	char				**command;
	t_builtin_function	*builtin;

	g_exit_code = 0;
	command = ft_lsttoa(lst);
	if ((builtin = is_builtin(command)) == NULL)
		ft_bin_exec(lst, command, *env);
	else
		ft_builtin_exec(builtin, lst, command, env);
	return (0);
}

/*
 * If the command is followed or proceeded by pipe, ft_handle_pipe will setup
 * the correct redirections and execute
 * else ft_run_command will execute the command.
 */

int			ft_execute(t_tokens *lst, char ***env)
{
	static int	*pipefd;

	if (lst->pipe_before || lst->pipe_after)
		pipefd = ft_handle_pipe(lst, pipefd, env);
	else
		ft_run_command(lst->command_tokens, env);
	return (0);
}

/*
 * Traverse AST and execute the token linked list.
 */

int			*ft_trav_exec(t_ast *root, char ***env)
{
	static int		and_or[2] = {-1, -1};

	if (root == NULL)
		return (and_or);
	ft_trav_exec(root->left, env);
	if (root->token->token_id == OR)
		and_or[1] = 1;
	else if (root->token->token_id == AND)
		and_or[0] = 1;
	else if (root->token->token_id == SEMI)
	{
		and_or[0] = -1;
		and_or[1] = -1;
	}
	if (root->token->token_id == SIMPLE_COMMAND)
	{
		if ((and_or[0] == -1 && and_or[1] == -1) || \
			((and_or[1] == 1 && g_exit_code != 0) \
				|| (and_or[0] == 1 && g_exit_code == 0)))
		{
			ft_execute(root->token, env);
			and_or[0] = -1;
			and_or[1] = -1;
		}
	}
	ft_trav_exec(root->right, env);
	return (and_or);
}
