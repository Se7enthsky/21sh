/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 02:31:32 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/20 10:50:32 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_tokens	*ft_lstnew_token(int token, char *value)
{
	t_tokens	*lst;

	if ((lst = ft_memalloc(sizeof(t_tokens))) == NULL)
		return (NULL);
	lst->value = value;
	lst->token_id = token;
	return (lst);
}

void		ft_lstdel_token(t_tokens **node)
{
	ft_memdel((void **)&(*node)->value);
	ft_memdel((void **)node);
}

void		ft_lstappend_token(t_tokens **node, int token, char *value)
{
	t_tokens	*lst;

	lst = *node;
	if (node == NULL)
		return ;
	else if (*node == NULL)
		*node = ft_lstnew_token(token, value);
	else
	{
		while (lst)
		{
			if (lst->next == NULL)
				break ;
			else
				lst = lst->next;
		}
		lst->next = ft_lstnew_token(token, value);
	}
}
