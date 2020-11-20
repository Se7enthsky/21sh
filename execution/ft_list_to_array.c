/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:36:08 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/20 10:51:45 by awali-al         ###   ########.fr       */
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
			command[index++] = list->value;
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
	if ((cmd = malloc(sizeof(char *) * (size + 1))) == NULL)
		exit(ENOMEM);
	cmd[size] = NULL;
	fill_array(list, cmd);
	return (cmd);
}
