/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 12:52:46 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/20 10:50:46 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/*
** Tokens
*/

static const t_id g_tokens[] =
{
	{"&&", AND, "AND"},
	{"||", OR, "OR"},
	{"|", PIPE, "PIPE"},
	{";", SEMI, "SEMI"},
	{"<<", DLESS, "Dless"},
	{"<", LESS, "less"},
	{">>", DGREAT, "Dgreat"},
	{">", GREAT, "Great"}
};

char	*ft_get_token_name(int id)
{
	unsigned int	i;

	i = 0;
	while (i < 8)
	{
		if (g_tokens[i].id == id)
			return (ft_strdup(g_tokens[i].name));
		i++;
	}
	return (ft_strdup("SIMPLE_COMMAND"));
}

int		ft_get_tokenid(const char *value, int id)
{
	unsigned int	i;
	int				len;

	i = 0;
	len = ft_strlen(value);
	if (id == WORD && len >= 2 && (ft_isdigit(*value) &&
			(*(value + 1) == '>' || *(value + 1) == '<')))
	{
		if (len > 2 && value[2] == '&' && value[1] == '>')
			return (FD_GREAT_AGR);
		else if (len > 2 && value[2] == '&' && value[1] == '<')
			return (FD_LESS_AGR);
		else if (len > 2 && value[2] != '&')
			return (FD_FILE);
		else if (len == 2 && *(value + 1) == '>')
			return (FD_GREAT);
	}
	while (i < 8)
	{
		if (ft_strcmp(g_tokens[i].token_value, value) == 0)
			return (g_tokens[i].id);
		i++;
	}
	return (id);
}
