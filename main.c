#include "21sh.h"
#include "tokenize.h"

int     main(void)
{
    char        *cmd;
    t_tokens    *head;

    head = NULL;
    while (1)
    {
        cmd = readline("$> ");
        ft_tokenize(&head, cmd);
        while (head)
        {
            printf("<%s, \"%s\">\n", ft_get_tokenname(head->token_id), head->value);
            head = head->next;
        }
    }
}