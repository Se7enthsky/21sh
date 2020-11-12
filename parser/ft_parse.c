/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:37:46 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/12 18:40:13 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define ARRAY_SIZE 13

/*
 * First check of syntax
 */

void	ft_get_alernative_ids(int token_id, int alt[], int size)
{
	int	i;

	i = 0;
	if (token_id == -1)
	{
		alt[0] = SIMPLE_COMMAND;
		alt[1] = WORD;
		alt[2] = SQ_STRING;
		alt[3] = DQ_STRING;
		alt[4] = FD_AGR;
		alt[5] = FD_FILE;
		alt[6] = FD_GREAT;
		i = 7;
	}
	if (token_id == SIMPLE_COMMAND)
	{
		alt[0] = PIPE;
		alt[1] = OR;
		alt[2] = AND;
		alt[3] = SEMI;
		i = 4;
	}
	else if (token_id >= 2 && token_id <= 6)
	{
		alt[0] = SIMPLE_COMMAND;
		i = 1;
	}
	else if (token_id >= 7 && token_id <= 11)
	{
		if (token_id == DLESS)
		{
			alt[0] = DELIMITER;
			i = 1;
		}
		else
		{
			alt[0] = FILENAME;
			i = 1;
		}
	}
	else if (token_id >= 12 && token_id <= 17)
	{
		alt[0] = LESS;
		alt[1] = DLESS;
		alt[2] = GREAT;
		alt[3] = DGREAT;
		alt[4] = WORD;
		alt[5] = SQ_STRING;
		alt[6] = DQ_STRING;
		alt[7] = FD_AGR;
		alt[8] = SEMI;
		alt[9] = FD_GREAT;
		alt[10] = FD_FILE;
		i = 11;
	}
	while (i < size)
		alt[i++] = 0;
}

int		ft_verify_syntax(t_tokens *lst)
{
	int		alternatives[ARRAY_SIZE];
	uint	i;
	uint	found;

	ft_get_alernative_ids(-1, alternatives, ARRAY_SIZE);
	while (lst)
	{
		i = 0;
		found = 0;
		while (i < ARRAY_SIZE)
		{
			if (lst->token_id == alternatives[i])
			{
				found = 1;
				break ;
			}
			i++;
		}
		if (found == 0)
			return (0);
		if (lst->token_id != SEMI && (lst->token_id >= 2 \
			&& lst->token_id <= 11))
		{
			if (lst->next == NULL)
				return (0);
		}
		ft_get_alernative_ids(lst->token_id, alternatives, ARRAY_SIZE);
		lst = lst->next;
	}
	return (1);
}

t_ast	*ft_new_astnode(t_tokens *node)
{
	t_ast	*ast_node;

	if (!(ast_node = ft_memalloc(sizeof(t_ast))))
		exit(ENOMEM);
	ast_node->token = node;
	return (ast_node);
}

/*
 *	Split linked list by (token_id), adding left half to the left tree node
 *	and right half to the right tree node.
 */

void	ft_ast_split(t_ast **root, int token_id)
{
	t_tokens	*lst;
	t_tokens	*left;
	t_tokens	*right;
	t_tokens	*temp;
	t_tokens	*current;

	lst = (*root)->token;
	temp = lst;
	while (lst)
	{
		if (lst->next && lst->next->token_id == token_id)
		{
			left = temp;
			right = lst->next->next;
			current = lst->next;
			if (current->token_id == PIPE)
			{
				right->pipe_before = 1;
				left->pipe_after = 1;
			}
			lst->next->next = NULL;
			lst->next = NULL;
			(*root)->token = current;
			if (right)
				(*root)->right = ft_new_astnode(right);
			if (left)
				(*root)->left = ft_new_astnode(left);
			break ;
		}
		lst = lst->next;
	}
}

/*
 *	Traverse Tree and split each linked list inside the node
 *	in the tree by (token_id)
 */

void	ft_ast_insert(t_ast **root, int token_id)
{
	if (root == NULL || *root == NULL)
		return ;
	ft_ast_insert(&(*root)->left, token_id);
	ft_ast_split(root, token_id);
	ft_ast_insert(&(*root)->right, token_id);
}

t_ast	*ft_build_ast(t_tokens *lst)
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

int		ft_traverse_verify(t_ast *root)
{
	if (root == NULL)
		return (1);
	if (ft_traverse_verify(root->left) == 0)
		return (0);
	if (root->token->token_id == SIMPLE_COMMAND && \
		ft_verify_syntax(root->token->command_tokens) == 0)
	{
		return (0);
	}
	if (ft_traverse_verify(root->right) == 0)
		return (0);
	return (1);
}

void	ft_join_heredoc(char *line, char **doc_str)
{
	char	*temp2;
	char	*temp;

	temp2 = ft_strjoin(line, "\n");
	temp = ft_strjoin(*doc_str, temp2);
	ft_memdel((void**)&temp2);
	ft_memdel((void**)doc_str);
	*doc_str = temp;
}

void	ft_heredoc_prompt(char *delimiter, char **doc_str)
{
	char	*line;

	while (1)
	{
		if ((line = readline("heredoc> ")))
		{
			if (ft_strcmp(delimiter, line))
				ft_join_heredoc(line, doc_str);
			else
			{
				ft_memdel((void**)&line);
				break ;
			}
		}
		else
			ft_putchar('\n');
	}
}

void	ft_parse_heredoc(t_tokens *head)
{
	char		*delimiter;

	while (head)
	{
		if (head->next && head->next->token_id == DLESS)
		{
			if (head->next->next)
				delimiter = head->next->next->value;
			head->next->heredoc = ft_strdup("");
			ft_heredoc_prompt(delimiter, &(head->next->heredoc));
		}
		head = head->next;
	}
}

void			ft_find_heredoc(t_ast *root)
{
	if (root == NULL)
		return ;
	ft_find_heredoc(root->left);
	if (root->token->token_id == SIMPLE_COMMAND)
		ft_parse_heredoc(root->token->command_tokens);
	ft_find_heredoc(root->right);
}

t_ast			*ft_parse(t_tokens *lst)
{
	t_ast			*root;

	if (ft_verify_syntax(lst) == 0)
		return (NULL);
	root = ft_build_ast(lst);
	if (ft_traverse_verify(root) == 0)
		return (NULL);
	ft_find_heredoc(root);
	return (root);
}
