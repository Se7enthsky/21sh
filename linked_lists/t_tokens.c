/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 02:31:32 by mobounya          #+#    #+#             */
/*   Updated: 2020/03/11 20:13:47 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

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
