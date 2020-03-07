#include <stdio.h>
#include "tokenize.h"

void	ft_tokenize_cmd(t_tokens **head, char *command);

typedef struct s_values
{
    char	*command;
    char	*tokens[50];
    int		ids[50];
} t_values;

t_values array[] =
{
	{"echo \"hello\"     ", {"echo", "\"hello\"", NULL}, {WORD, DQ_STRING}},
    {"echo <<", {"echo", "<<", NULL}, {WORD, DLESS}},
    {"cat -e << EOF", {"cat", "-e", "<<", "EOF", NULL}, {WORD, WORD, DLESS, WORD}},
    {"<<", {"<<", NULL}, {DLESS}},
    {">>", {">>", NULL}, {DGREAT}},
    {"<", {"<", NULL}, {LESS}},
    {">", {">", NULL}, {GREAT}},
    {"echo \'aaa\' << ddd", {"echo", "\'aaa\'", "<<", "ddd", NULL}, {WORD, SQ_STRING, DLESS, WORD}},
    {"< << > >>", {"<", "<<", ">", ">>", NULL}, {LESS, DLESS, GREAT, DGREAT}},
    {"cat < file > file2", {"cat", "<", "file", ">", "file2", NULL}, {WORD, LESS, WORD, GREAT, WORD}},
    {"<< >>", {"<<", ">>", NULL}, {DLESS, DGREAT}},
    {"", {"", NULL}, {WORD}},
    {"a", {"a", NULL}, {WORD}},
    {">> << > <", {">>", "<<", ">", "<"}, {DGREAT, DLESS, GREAT, LESS}},
    {"> >> < <<", {">", ">>", "<", "<<"}, {GREAT, DGREAT, LESS, DLESS}},
    {"word", {"word", NULL}, {WORD}},
    {"< >", {"<", ">", NULL}, {LESS, GREAT}},
    {"> >", {">", ">", NULL}, {GREAT, GREAT}},
    {"echo >           ", {"echo", ">", NULL}, {WORD, GREAT}},
    {"echo >           >", {"echo", ">", ">", NULL}, {WORD, GREAT, GREAT}},
    {"echo >           >                  " , {"echo", ">", ">", NULL}, {WORD, GREAT, GREAT}},
    {"echo                                   >                 file          2<&-", {"echo", ">", "file", "2<&-", NULL}, {WORD, GREAT, WORD, WORD}},
    {"                                 >", {">", NULL}, {GREAT}},
    {"                                 >>", {">>", NULL}, {DGREAT}},
    {"                                 <", {"<", NULL}, {LESS}},
    {"                                 <<", {"<<", NULL}, {DLESS}},
};

#define ARRAY_SIZE 26

int main(void)
{
    t_tokens *head;
    int pid;
    int status;
    int test;
    int     unit_test;

    head = NULL;
    for (test = 0; test < ARRAY_SIZE; test++)
    {
        printf("************ Test #%d *************\n", test + 1);
        pid = fork();
        if (pid == 0)
        {
            ft_tokenize_cmd(&head, array[test].command);
            unit_test = 0;
            while (head)
            {
				printf("-----> Token test #%d <--------\n", unit_test);
				if (ft_strcmp(array[test].tokens[unit_test], head->value) == 0)
                    printf("\e[32mSuccess\e[0m\n");
                else
                {
                    printf("  \e[91mFalse\e[0m\n");
                    printf("Expected: `%s` || Result: `%s`\n", array[test].tokens[unit_test], head->value);
                }
				if (head->token_id == array[test].ids[unit_test])
					printf("\e[32m--> Id Match\e[0m\n");
				else
				{
					printf("\e[91m--> Id Doesen't match\e[0m\n");
					printf("\tExpected id : `%d` || Result id: `%d`\n", array[test].ids[unit_test], head->token_id);
				}
                head = head->next;
                unit_test++;
            }
            printf("---------------------\n");
            free(head);
            head = NULL;
			return (0);
        }
        else
        {
            wait(&status);
            if (WIFSIGNALED(status))
            {
                if (status == SIGSEGV)
                    printf(" SegFault\n--------------------------\n");
            }
        }
    }
	return (0);
}