/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:07:40 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/30 16:51:06 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_processes			*ft_lstnew_tprocs(pid_t pid)
{
	t_processes		*new_node;

	if ((new_node = ft_memalloc(sizeof(t_processes))) == NULL)
		exit(ENOMEM);
	new_node->pid = pid;
	return (new_node);
}

void				ft_add_process(t_processes **lst, pid_t pid)
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

void				ft_lstprocs_wait(t_processes *lst)
{
	while (lst)
	{
		kill(lst->pid, SIGKILL);
		lst = lst->next;
	}
}
