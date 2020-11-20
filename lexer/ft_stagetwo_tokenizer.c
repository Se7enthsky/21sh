/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stagetwo_tokenizer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 14:04:24 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/20 13:02:36 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char		*cut_append_qstring(t_tokens **head, char *command)
{
	char	*temp;
	char	*value;
	int		token_id;

	value = NULL;
	if ((temp = ft_strchr(command + 1, *command)))
	{
		value = ft_strsub(command, 0, (temp - command) + 1);
		token_id = (*command == '\"') ? DQ_STRING : SQ_STRING;
		ft_lstappend_token(head, token_id, value);
	}
	return (temp);
}

char		*cut_append_word(t_tokens **head, char *command)
{
	unsigned int	i;
	char			*value;

	i = 0;
	while (command[i] && !is_ws(command[i]) &&
		command[i] != '\"' && command[i] != '\'')
		i++;
	value = ft_strsub(command, 0, i);
	ft_lstappend_token(head, ft_get_tokenid(value, WORD), value);
	return (command + i);
}

void		ft_stagetwo_tokenizer(t_tokens **head, char *command)
{
	uint	i;

	while (*command)
	{
		if (*command == '\"' || *command == '\'')
		{
			command = cut_append_qstring(head, command);
			if (command)
				command++;
			else
			{
				ft_putendl_fd("Syntax Error", 2);
				exit(1);
			}
		}
		else
		{
			i = 0;
			while (*command && is_ws(*command))
				command++;
			if (*command && *command != '\'' && *command != '\"')
				command = cut_append_word(head, command);
		}
	}
}
