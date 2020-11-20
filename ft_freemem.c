/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freemem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 02:21:13 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/20 10:49:24 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void	ft_free_arr(char **ar)
{
	unsigned int	i;

	i = 0;
	if (ar == NULL || *ar == NULL)
		return ;
	while (ar[i])
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}

void	ft_free_tokens(t_tokens *token)
{
	t_tokens	*temp;

	while (token)
	{
		ft_memdel((void**)&(token->value));
		ft_memdel((void**)&(token->heredoc));
		if (token->command_tokens)
			ft_free_tokens(token->command_tokens);
		temp = token->next;
		ft_memdel((void**)&token);
		token = temp;
	}
}

void	ft_free_ast(t_ast **root)
{
	if (root == NULL || *root == NULL)
		return ;
	ft_free_ast(&(*root)->left);
	if ((*root)->token)
		ft_free_tokens((*root)->token);
	ft_free_ast(&(*root)->right);
	ft_memdel((void**)root);
}
