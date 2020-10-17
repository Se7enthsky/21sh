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

#endif