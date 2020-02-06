#include "21sh.h"

/*
 * List of available tokens.
 */

# define FULL_COMMAND	1
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
 *  Lexer Functions.
 */

void	ft_tokenize(t_tokens **head, char *command);
char	*ft_get_tokenname(int token_id);
int		ft_get_tokenid(char *token_value);

/*
 * Functions for manipulating tokens list.
 */

t_tokens	*ft_lstnew_token(int token, char *value);
void		ft_lstdel_token(t_tokens **node);
void		ft_lstappend_token(t_tokens **node, int token, char *value);

/*
 * Struct of tokens and their respactive identifier.
 */

typedef struct	s_id
{
    char		*token_value;
    int         id;
	char		*name;
}				t_id;