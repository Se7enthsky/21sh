#include <stdio.h>
#include "tokenize.h"

typedef struct s_values
{
    char	*command;
    char	*tokens[50];
    int		ids[50];
} t_values;

static const t_id my_seperators[] =
{
	{"&&", AND, "AND"},
    {"||", OR, "OR"},
	{"|", PIPE, "Pipe"},
	{";", SEMI, "Semi"},
	{NULL, 0, NULL},
};

t_values array[] =
{
	{"echo \"hello\"     ", {"echo \"hello\"", NULL}, {SIMPLE_COMMAND}},
	{"echo \"hello\" ; pwd", {"echo \"hello\"", ";", "pwd", NULL}, {SIMPLE_COMMAND, SEMI, SIMPLE_COMMAND}},
	{"|", {"|", NULL}, {PIPE}},
	{"&&", {"&&", NULL}, {AND}},
	{"||", {"||", NULL}, {OR}},
	{";", {";", NULL}, {SEMI}},
	{"echo \"fpp\" || cat -e ; pwd && foo", {"echo \"fpp\"", "||", "cat -e", ";", "pwd", "&&", "foo", NULL}, {SIMPLE_COMMAND, OR, SIMPLE_COMMAND, SEMI, SIMPLE_COMMAND, AND, SIMPLE_COMMAND}},
	{"echo foo && cat -e ; pwd || ls >> file | touch && pwd = ppp", {"echo foo", "&&", "cat -e", ";", "pwd", "||", "ls >> file", "|", "touch", "&&", "pwd = ppp", NULL}, {SIMPLE_COMMAND, AND, SIMPLE_COMMAND, SEMI, SIMPLE_COMMAND, OR, SIMPLE_COMMAND, PIPE, SIMPLE_COMMAND, AND, SIMPLE_COMMAND}},
	{"ls >> file", {"ls >> file", NULL}, {SIMPLE_COMMAND}},
	{"echo ff || sss == sss && cat << EOF", {"echo ff", "||", "sss == sss", "&&", "cat << EOF", NULL}, {SIMPLE_COMMAND, OR, SIMPLE_COMMAND, AND, SIMPLE_COMMAND}},
    {"&", {"&", NULL}, {SIMPLE_COMMAND}},
    {"|", {"|", NULL}, {PIPE}},
    {"|||", {"||", "|", NULL}, {OR, PIPE}},
    {";;;", {";", ";", ";", NULL}, {SEMI, SEMI, SEMI}},
    {"&&&", {"&&", "&", NULL}, {AND, SIMPLE_COMMAND}},
    {"echo               \"aaa\"      ;                                                                                   pwd", {"echo               \"aaa\"", ";", "pwd", NULL}, {SIMPLE_COMMAND, SEMI, SIMPLE_COMMAND}},
    {"", {"", NULL}, {SIMPLE_COMMAND}},
    {"&&|||;", {"&&", "|", "||", ";", NULL}, {AND, PIPE, OR, SEMI}},
    {"a", {"a", NULL}, {SIMPLE_COMMAND}},
    {" ", {"", NULL}, {SIMPLE_COMMAND}},
    {"echo &&", {"echo", "&&", NULL}, {SIMPLE_COMMAND, AND}},
    {"echo &&                 &&", {"echo", "&&", "&&", "a", NULL}, {SIMPLE_COMMAND, AND, AND}},
    {"echo ||                  ||", {"echo", "||", "||", "b", NULL}, {SIMPLE_COMMAND, OR, OR}},
};

#define ARRAY_SIZE 23

int main(void)
{
    t_tokens	*head;
    int			pid;
    int			status;
    int			test;
    int			unit_test;

    head = NULL;
    for (test = 0; test < ARRAY_SIZE; test++)
    {
        printf("************ Test #%d *************\n", test + 1);
        pid = fork();
        if (pid == 0)
        {
            ft_tokenize(&head, array[test].command, my_seperators);
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