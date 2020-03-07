#ifndef TOKENIZE_H
#define TOKENIZE_H
#include "21sh.h"

/*
 * List of all available tokens.
 */

# define SIMPLE_COMMAND	1
# define PIPE			2
# define OR				3
# define AND			4
# define SEMI           6

# define LESS           7
# define DLESS          8
# define GREAT			9
# define DGREAT			10
# define WORD           11
# define SQ_STRING      12
# define DQ_STRING      13
# define FD_AGR         14

/*
 * Ends Here.
 */


/*
 * Tokens linked list.
 */

typedef struct	s_tokens t_tokens;

struct	s_tokens
{
    int				token_id;
    char            *value;
    t_tokens        *next;
    t_tokens        *command_tokens;
};

/*
 * Struct of tokens and their respactive identifier.
 */

typedef struct	s_id
{
    char		*token_value;
    int         id;
	char		*name;
}				t_id;

/*
 *  Lexer Functions.
 */

void    ft_tokenize(t_tokens **head, char *command, const t_id seperators[]);
int		ft_strchri(const char *str, char c);
int		ft_get_tokenid(const char *value, int id);
char	*ft_get_token_name(int id);

/*
 * Functions for manipulating tokens list.
 */

t_tokens	*ft_lstnew_token(int token, char *value);
void		ft_lstdel_token(t_tokens **node);
void		ft_lstappend_token(t_tokens **node, int token, char *value);

#endif