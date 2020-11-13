/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_syntx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 17:52:45 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/13 18:04:42 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define ARRAY_SIZE 13

int		starter_ids(int alt[])
{
	int		i;

	alt[0] = SIMPLE_COMMAND;
	alt[1] = WORD;
	alt[2] = SQ_STRING;
	alt[3] = DQ_STRING;
	alt[4] = FD_AGR;
	alt[5] = FD_FILE;
	alt[6] = FD_GREAT;
	i = 7;
	return (i);
}

int		seperators_id(int alt[])
{
	int		i;

	alt[0] = PIPE;
	alt[1] = OR;
	alt[2] = AND;
	alt[3] = SEMI;
	i = 4;
	return (i);
}

int		function(int alt[])
{
	int		i;

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
	return (i);
}

void	ft_get_alernative_ids(int token_id, int alt[], int size)
{
	int	i;

	i = 0;
	if (token_id == -1)
		i = starter_ids(alt);
	if (token_id == SIMPLE_COMMAND)
		i = seperators_id(alt);
	else if (token_id >= 2 && token_id <= 6)
	{
		alt[0] = SIMPLE_COMMAND;
		i = 1;
	}
	else if (token_id >= 7 && token_id <= 11)
	{
		alt[0] = (token_id == DLESS) ? DELIMITER : FILENAME;
		i = 1;
	}
	else if (token_id >= 12 && token_id <= 17)
		i = function(alt);
	while (i < size)
		alt[i++] = 0;
}

int		ft_compare_token(int token_id, int alt[])
{
	unsigned int	i;

	i = 0;
	while (i < ARRAY_SIZE)
	{
		if (token_id == alt[i])
			return (1);
		i++;
	}
	return (0);
}

/*
 * First check of syntax
 */

int		ft_verify_syntax(t_tokens *lst)
{
	int		alternatives[ARRAY_SIZE];

	ft_get_alernative_ids(-1, alternatives, ARRAY_SIZE);
	while (lst)
	{
		if ((ft_compare_token(lst->token_id, alternatives)) == 0)
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
