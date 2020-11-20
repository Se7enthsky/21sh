/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:37:46 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/20 10:50:22 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	ft_fill_ast(t_ast *root, t_tokens *left,\
		t_tokens *current, t_tokens *right)
{
	if (current->token_id == PIPE)
	{
		right->pipe_before = 1;
		left->pipe_after = 1;
	}
	root->token = current;
	if (right)
		root->right = ft_new_astnode(right);
	if (left)
		root->left = ft_new_astnode(left);
}

/*
**	Split linked list by (token_id), adding left half to the left tree node
**	and right half to the right tree node.
*/

void	ft_ast_split(t_ast **root, int token_id)
{
	t_tokens	*lst;
	t_tokens	*temp;

	lst = (*root)->token;
	temp = lst;
	while (lst)
	{
		if (lst->next && lst->next->token_id == token_id)
		{
			ft_fill_ast(*root, temp, lst->next, lst->next->next);
			lst->next->next = NULL;
			lst->next = NULL;
			break ;
		}
		lst = lst->next;
	}
}

/*
**	Traverse Tree and split each linked list inside the node
**	in the tree by (token_id)
*/

void	ft_ast_insert(t_ast **root, int token_id)
{
	if (root == NULL || *root == NULL)
		return ;
	ft_ast_insert(&(*root)->left, token_id);
	ft_ast_split(root, token_id);
	ft_ast_insert(&(*root)->right, token_id);
}

t_ast	*ft_split_list(t_tokens *lst)
{
	t_ast			*root;
	const int		seperators[4] = {SEMI, AND, OR, PIPE};
	int				i;

	i = 0;
	root = ft_new_astnode(lst);
	while (i < 4)
	{
		ft_ast_insert(&root, seperators[i]);
		i++;
	}
	return (root);
}

t_ast	*ft_parse(t_tokens *lst)
{
	t_ast			*root;

	if (ft_verify_syntax(lst) == 0)
		return (NULL);
	root = ft_split_list(lst);
	if (ft_traverse_verify(root) == 0)
		return (NULL);
	ft_find_heredoc(root);
	return (root);
}
