/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freemem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 02:21:13 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/03 02:49:51 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "parser.h"

void	ft_free_tokens(t_tokens	*token)
{
	t_tokens	*temp;

	while (token)
	{
		ft_memdel((void**)&(token->value));
		if (token->command_tokens)
			ft_free_tokens(token->command_tokens);
		temp = token->next;
		ft_memdel((void**)&token);
		token = temp;
	}
}

void    ft_free_ast(t_ast   **root)
{
    if (root == NULL || *root == NULL)
        return ;
    ft_free_ast(&(*root)->left);
	if ((*root)->token)
		ft_free_tokens((*root)->token);
	ft_free_ast(&(*root)->right);
	ft_memdel((void**)root);
}