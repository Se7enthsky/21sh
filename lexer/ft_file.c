/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:13:11 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/23 17:13:46 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	ft_set_filenames(t_tokens *list)
{
	int token_id;

	while (list)
	{
		token_id = list->token_id;
		if (token_id == GREAT || token_id == DGREAT ||
			token_id == LESS || token_id == FD_GREAT || token_id == DLESS)
		{
			if (list->next)
			{
				token_id = list->next->token_id;
				if (token_id == WORD || token_id == SQ_STRING ||
					token_id == DQ_STRING)
				{
					if (list->token_id == DLESS)
						list->next->token_id = DELIMITER;
					else
						list->next->token_id = FILENAME;
				}
			}
		}
		list = list->next;
	}
}

void	ft_substitution(t_tokens *list, char **env)
{
	char *temp;

	while (list)
	{
		temp = list->value;
		list->value = ft_replace_variables(ft_strdup(list->value), env);
		free(temp);
		if (list->value)
		{
			if ((list->value[0] == '~' && ft_strlen(list->value) == 1) ||
				(ft_strlen(list->value) > 1 && list->value[0] == '~' &&
				list->value[1] == '/'))
			{
				temp = list->value;
				list->value = ft_replace_home(list->value, env);
				free(temp);
			}
		}
		list = list->next;
	}
}

void	ft_get_cmd(t_tokens *head, char **env)
{
	while (head)
	{
		if (head->token_id == SIMPLE_COMMAND)
		{
			ft_stagetwo_tokenizer(&head->command_tokens, head->value);
			ft_set_filenames(head->command_tokens);
			ft_substitution(head->command_tokens, env);
		}
		head = head->next;
	}
}
