#ifndef PARSER_H
#define PARSER_H

#include "tokenize.h"
#include "../readline/includes/to_sh_rl.h"

typedef struct	s_ast t_ast;

struct  s_ast
{
    t_tokens	*token;
    int         first_token_id;
	t_ast		*right;
	t_ast		*left;
};

void    ft_free_arr(char **ar);

/*
 *	Functions to verify syntax in both stages
 */

int		ft_verify_syntax(t_tokens *lst);
int		ft_traverse_verify(t_ast *root);

/*
 * Function to find here doc in the tree and parse it,
 * other helper functions are in /parser/ft_heredoc.c
 */

void    ft_find_heredoc(t_ast *root);
#endif