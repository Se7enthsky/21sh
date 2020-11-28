/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:49:07 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/26 00:09:25 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenize.h"

# define ARRAY_SIZE		13

typedef struct s_ast	t_ast;

struct					s_ast
{
	t_tokens			*token;
	int					first_token_id;
	t_ast				*right;
	t_ast				*left;
};

void					ft_free_arr(char **ar);
int						ft_compare_token(int token_id, int alt[]);
void					ft_get_alernative_ids(int token_id, int alt[],
		int size);
t_ast					*ft_new_astnode(t_tokens *node);
t_ast					*ft_build_ast(char *cmd, char **env);

/*
**	Functions to verify syntax in both stages
*/

int						ft_verify_syntax(t_tokens *lst);
int						ft_traverse_verify(t_ast *root);

/*
** Function to find here doc in the tree and parse it,
** other helper functions are in /parser/ft_heredoc.c
*/

int						ft_find_heredoc(t_ast *root, int c);

/*
** checking the quotes and double quotes
*/

#endif
