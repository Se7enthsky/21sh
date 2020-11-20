/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:25:33 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/20 18:21:56 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_processes	*g_procs_lst = NULL;

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
** If the command is followed or proceeded by pipe, ft_handle_pipe will setup
** the correct redirections and execute
** else ft_run_command will execute the command.
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
** Traverse AST and execute the token linked list.
*/

void		ft_trav_exec(t_ast *root, char ***env)
{
	static int		and_or[2] = {-1, -1};

	if (root == NULL)
		return ;
	ft_trav_exec(root->left, env);
	if (root->token->token_id == OR)
		and_or[1] = 1;
	else if (root->token->token_id == AND)
		and_or[0] = 1;
	else if (root->token->token_id == SEMI)
		ft_reset(and_or);
	if (root->token->token_id == SIMPLE_COMMAND)
	{
		if ((and_or[0] == -1 && and_or[1] == -1) || \
			((and_or[1] == 1 && g_exit_code != 0) \
				|| (and_or[0] == 1 && g_exit_code == 0)))
		{
			ft_execute(root->token, env);
			ft_reset(and_or);
		}
	}
	ft_trav_exec(root->right, env);
}
