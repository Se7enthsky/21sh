#include "tokenize.h"

void	ft_tokenize_cmd(t_tokens **head, char *command)
{
	uint	i;
	char	*temp;
	char	*value;

	while (*command)
	{
		if (*command == '\"' || *command == '\'')
		{
			if ((temp = ft_strchr(command + 1, *command)))
			{
				value = ft_strsub(command, 0, (temp - command) + 1);
				ft_lstappend_token(head, (*command == '\"') ? DQ_STRING : SQ_STRING, value);
				command = temp + 1;
			}
			else
			{
				printf("Syntax Error\n");
				exit(0);
			}
		}
		else
		{
			i = 0;
			while (*command && IS_WS(*command))
				command++;
			if (*command && *command != '\'' && *command != '\"')
			{
				while (command[i] && !IS_WS(command[i]) && \
				command[i] != '\"' && command[i] != '\'')
					i++;
				value = ft_strsub(command, 0, i);
				ft_lstappend_token(head, ft_get_tokenid(value, 11), value);
				command = command + i;
			}
		}
	}
}

void	ft_get_cmd(t_tokens *head)
{
	while (head)
	{
		if (head->token_id == SIMPLE_COMMAND)
			ft_tokenize_cmd(&head->command_tokens, head->value);
		head = head->next;
	}
}