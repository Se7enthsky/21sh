#ifndef PARSER_H
#define PARSER_H

#include "tokenize.h"

typedef struct	s_ast t_ast;

struct  s_ast
{
    t_tokens	*token;
    int         first_token_id;
	t_ast		*right;
	t_ast		*left;
};

#endif