#include "main.h"

/*
 *  Seperators for the full command, coming directly from user input.
 *    Example of full command : "echo "foo" >> bar | pwd ; cat -e << EOF && ls -l dir1 dir2"
 */

void ft_get_cmd(t_tokens *head);

static const t_id seperators[] =
{
    {"&&", DGREAT, "Dgreat"}, 
    {"||", OR, "OR"},
    {"|", PIPE, "Pipe"},
    {";", SEMI, "Semi"},
    {NULL, 0, NULL},
};

t_ast   *ft_parse(t_tokens *lst);
int     *ft_execute(t_ast *root);

int     main(void)
{
    t_ast		*root;
    t_tokens	*head;
    char		*cmd;
    int         *and_or;
 
    head = NULL;
    while (1)
    {
        if ((cmd = readline("$> ")))
        {
            ft_tokenize(&head, cmd, seperators);
            if (head)
            {
                ft_get_cmd(head);
                if ((root = ft_parse(head)) == NULL)
                    ft_putendl_fd("21sh: parse error", 2);
                else
                {
                    and_or = ft_execute(root);
                    and_or[0] = -1;
                    and_or[1] = -1;
                }
                ft_memdel((void **)&head);
                ft_memdel((void **)&root);
            }
        }
        else
            ft_putchar('\n');
    }
}