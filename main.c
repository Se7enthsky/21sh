#include "main.h"
#include <sys/errno.h>
#include <unistd.h>

extern char		**environ;

void    ft_get_cmd(t_tokens *head, char **env);
t_ast   *ft_parse(t_tokens *lst);
int     *ft_execute(t_ast *root, char ***env);
int		ft_arraysize(char **ar);

/*
 *  Seperators for the full command, coming directly from user input.
 *    Example of full command : "echo "foo" >> bar | pwd ; cat -e << EOF && ls -l dir1 dir2"
 */

static const t_id seperators[] =
{
    {"&&", DGREAT, "Dgreat"}, 
    {"||", OR, "OR"},
    {"|", PIPE, "Pipe"},
    {";", SEMI, "Semi"},
    {NULL, 0, NULL},
};


char    **ft_envinit(void)
{
    char			**new_env;
    size_t			size;
    unsigned int    i;

	i = 0;
    size = ft_arraysize(environ);
    if ((new_env = malloc(sizeof(char *) * size + 1)) == NULL)
        exit(ENOMEM);
    while (i < size)
	{
		new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int     main(void)
{
    t_ast		*root;
    t_tokens	*head;
    char		*cmd;
    int         *and_or;
    char        **env;

    head = NULL;
    env = ft_envinit();
    while (1)
    {
        if ((cmd = readline("$> ")))
        {
            ft_tokenize(&head, cmd, seperators);
            if (head)
            {
                ft_get_cmd(head, env);
                if ((root = ft_parse(head)) == NULL)
                    ft_putendl_fd("21sh: parse error", 2);
                else
                {
                    and_or = ft_execute(root, &env);
                    and_or[0] = -1;
                    and_or[1] = -1;
                }
                ft_memdel((void **)&root);
                ft_memdel((void **)&head);
            }
        }
        else
            ft_putchar('\n');
    }
}
