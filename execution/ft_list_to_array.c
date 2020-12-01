/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:36:08 by mobounya          #+#    #+#             */
/*   Updated: 2020/12/01 00:28:46 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char		*ft_remove_quote(char *value)
{
	char	*string;

	value[ft_strlen(value) - 1] = '\0';
	string = ft_strdup(value + 1);
	return (string);
}

void		fill_array(t_tokens *list, char **command)
{
	uint	index;
	char	*string;

	index = 0;
	while (list)
	{
		if (list->token_id == DQ_STRING || list->token_id == SQ_STRING)
		{
			string = ft_remove_quote(list->value);
			free(list->value);
			list->value = string;
			command[index] = string;
			index++;
		}
		else if (list->token_id == WORD)
			command[index++] = ft_strdup(list->value);
		list = list->next;
	}
}

char		**ft_lsttoa(t_tokens *list)
{
	int			size;
	char		**cmd;
	t_tokens	*temp;

	size = 0;
	temp = list;
	while (temp)
	{
		if (temp->token_id == WORD || temp->token_id == SQ_STRING \
			|| temp->token_id == DQ_STRING)
			size++;
		temp = temp->next;
	}
	if ((cmd = ft_memalloc(sizeof(char *) * (size + 1))) == NULL)
		exit(ENOMEM);
	fill_array(list, cmd);
	cmd[size] = NULL;
	return (cmd);
}
