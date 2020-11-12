/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 20:30:30 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/12 12:39:37 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "tokenize.h"
#include "errors.h"
#define RD 0
#define WR 1

extern int g_exit_code;
extern t_processes *g_procs_lst;

t_processes		*ft_lstnew_tprocs(pid_t pid)
{
	t_processes		*new_node;

	if ((new_node = ft_memalloc(sizeof(t_processes))) == NULL)
		exit(ENOMEM);
	new_node->pid = pid;
	return (new_node);
}

void			ft_add_process(t_processes **lst, pid_t pid)
{
	t_processes	*list;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = ft_lstnew_tprocs(pid);
	else
	{
		list = *lst;
		while (list)
		{
			if (list->next)
				list = list->next;
			else
				break ;
		}
		list->next = ft_lstnew_tprocs(pid);
	}
	return ;
}

void			ft_lstprocs_wait(t_processes *lst)
{
	while (lst)
	{
		waitpid(lst->pid, NULL, 0);
		lst = lst->next;
	}
}

int				*ft_create_pipe(void)
{
	int		*newpipefd;

	if ((newpipefd = malloc(sizeof(int) * 2)) == NULL)
		exit(ENOMEM);
	pipe(newpipefd);
	return (newpipefd);
}

void			ft_set_pipe(int read_end, int write_end)
{
	if (read_end > 0)
		dup2(read_end, STDIN_FILENO);
	if (write_end > 0)
		dup2(write_end, STDOUT_FILENO);
}

int				ft_dup_exec(t_tokens *lst, int write_end, \
				int read_end, char ***env)
{
	pid_t				pid;
	char				**command;
	t_builtin_function	*builtin;

	command = ft_lsttoa(lst);
	g_exit_code = 0;
	if ((pid = fork()) == 0)
	{
		ft_set_pipe(read_end, write_end);
		if ((builtin = is_builtin(command)) == NULL)
			ft_exec_command(lst, command, *env);
		else
			ft_builtin_exec(builtin, lst, command, env);
		exit(g_exit_code);
	}
	else
		waitpid(pid, &g_exit_code, 0);
	if (write_end)
		close(write_end);
	return (pid);
}

/*
 * Create pipe for reading and writing,
 *	and pass it to ft_dupexecute for executing.
 */

int					*ft_handle_pipe(t_tokens *lst, int *pipefd, char ***env)
{
	int		*newpipefd;
	pid_t	pid;

	newpipefd = NULL;
	if (lst->pipe_before && lst->pipe_after)
	{
		newpipefd = ft_create_pipe();
		pid = ft_dup_exec(lst->command_tokens, newpipefd[WR], pipefd[RD], env);
		ft_add_process(&g_procs_lst, pid);
		ft_memdel((void**)&pipefd);
	}
	else if (lst->pipe_after)
	{
		newpipefd = ft_create_pipe();
		pid = ft_dup_exec(lst->command_tokens, newpipefd[WR], -1, env);
		ft_add_process(&g_procs_lst, pid);
	}
	else if (lst->pipe_before)
	{
		pid = ft_dup_exec(lst->command_tokens, -1, pipefd[RD], env);
		ft_add_process(&g_procs_lst, pid);
		ft_lstprocs_wait(g_procs_lst);
		ft_memdel((void**)&pipefd);
	}
	return (newpipefd);
}
