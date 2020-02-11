#include "21sh.h"
#include "tokenize.h"

/*
 *  Seperators for the full command, coming directly from user input.
 *    Example of full command : "echo "foo" >> bar | pwd ; cat -e << EOF && ls -l dir1 dir2"
 */

static const t_id    seperators[] =
{
    {"&&", DGREAT, "Dgreat"},
    {"||", OR, "OR"},
    {"|", PIPE, "Pipe"},
    {";", SEMI, "Semi"},
};

void	ft_get_cmd(t_tokens *head);

int     main(void)
{
    char        *cmd;
    t_tokens    *head;

    head = NULL;
    while (1)
    {
        if ((cmd = readline("$> ")))
        {
            ft_tokenize(&head, cmd, seperators);
            ft_get_cmd(head);
            while (head)
            {
                printf("%s\n", head->value);
                head = head->next;
            }
        }
        else
            ft_putchar('\n');
    }
}