/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_astnode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:37:34 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/17 12:37:36 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*ft_new_astnode(t_tokens *node)
{
	t_ast	*ast_node;

	if (!(ast_node = ft_memalloc(sizeof(t_ast))))
		exit(ENOMEM);
	ast_node->token = node;
	return (ast_node);
}
