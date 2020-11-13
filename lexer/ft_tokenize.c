/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:06:30 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/13 18:24:55 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

uint	find_seperator(const char *command, const t_id seps[], int *sep_index)
{
	unsigned int	i;
	unsigned int	j;
	char			*token_value;

	i = 0;
	while (command[i])
	{
		j = 0;
		while (seps[j].token_value)
		{
			token_value = seps[j].token_value;
			if (!ft_strncmp(command + i, token_value, ft_strlen(token_value)))
			{
				*sep_index = j;
				return (i);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

void	append_value(t_tokens **head, char *value)
{
	char	*trimmed_value;
	int		token_id;

	trimmed_value = ft_strtrim(value);
	if (trimmed_value && *trimmed_value)
	{
		token_id = ft_get_tokenid(trimmed_value, 1);
		ft_lstappend_token(head, token_id, trimmed_value);
	}
}

void	ft_split_commande(t_tokens **head, char *cmd, int start, size_t len)
{
	char	*value;

	value = ft_strsub(cmd, start, len);
	append_value(head, value);
	ft_memdel((void**)&value);
}

void	ft_tokenize(t_tokens **head, char *command, const t_id seps[])
{
	int		i;
	int		sep_index;
	int		last_index;
	int		res;

	i = 0;
	last_index = 0;
	while (command[i])
	{
		if (command[i] == '\"' || command[i] == '\'')
			i += (ft_strchri(command + i + 1, command[i]) + 1) + 1;
		if ((res = find_seperator(command + i, seps, &sep_index)) > -1)
		{
			i += res;
			ft_split_commande(head, command, last_index, i - last_index);
			ft_split_commande(head, command, i, \
				ft_strlen(seps[sep_index].token_value));
			i += ft_strlen(seps[sep_index].token_value);
			last_index = i;
		}
		i += command[i] != '\0';
	}
	if (*(command + last_index))
		append_value(head, command + last_index);
}
