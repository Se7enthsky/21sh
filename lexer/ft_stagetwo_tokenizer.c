/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stagetwo_tokenizer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 14:04:24 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/20 14:58:38 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char		*cut_append_qstring(char *command)
{
	int		i;
	char	*temp;
	char	*line;
	t_hist	*his;

	i = 0;
	his = open_hist();
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '\"')
		{
			i = ft_strchri(command + i + 1, command[i]);
			if (i == -1)
			{
				i = ft_strlen(command) - 1;
				temp = command;
				line = get_line(&his, "q> ", 1);
				command = ft_strjoin(temp, line);
				write(1, "\n", 1);
				// ft_memdel((void**)&temp);
				// ft_memdel((void**)&line);
				i = -1;
			}
		}
		i++;
	}
	ft_putendl("bahlaoui gay");
	// free_his(&his);
	return (command);
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
			command = cut_append_qstring(command);
			printf("%s\n", command);
			exit(1);
			if (command)
				command++;
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
