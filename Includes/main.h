#ifndef MAIN_H
#define MAIN_H
#include "21sh.h"
#include "tokenize.h"
#include "parser.h"

typedef struct s_env
{
    char            **env;
    unsigned int    size;
}   t_env;

void    ft_get_cmd(t_tokens *head, char **env);
t_ast   *ft_parse(t_tokens *lst);
int     *ft_trav_exec(t_ast *root, char ***env);
int     ft_arraysize(char **ar);
void    ft_free_ast(t_ast   **root);

#endif