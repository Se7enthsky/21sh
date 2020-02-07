#include "tokenize.h"

/*
 * Tokens
 */

static const t_id    tokens[] =
{
	{"&&", DGREAT, "Dgreat"},
	{"||", OR, "OR"},
	{"|", PIPE, "Pipe"},
	{";", SEMI, "Semi"},
	{"<<", DLESS, "Dless"},
	{"<", LESS, "less"},
	{">>", DGREAT, "Dgreat"},
	{">", GREAT, "Great"},
};

int		ft_get_tokenid(const char *value, int id)
{
	unsigned int	i;

	i = 0;
	while (i < 8)
	{
		if (!ft_strcmp(tokens[i].token_value, value))
			return (tokens[i].id);
		i++;
	}
	return (id);
}

int		ft_strchri(const char *str, char c)
{
	int		i;
  
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}


void    ft_tokenize(t_tokens **head, char *command, const t_id seperators[])
{
    int		i;
	int		seperators_index;
	int		last_index;
	char	*value;
	char	*value2;

	i = 0;
    last_index = 0;
	while (command[i])
	{
		seperators_index = 0;
		if (command[i] == '\"' || command[i] == '\'')
		{
			i += ft_strchri(command + i + 1, command[i]) + 1;
			i = i + 1;
		}
		while (seperators[seperators_index].token_value)
		{
			if (ft_strequ(command + i, seperators[seperators_index].token_value))
			{
				value = ft_strsub(command, last_index, i - last_index);
				if (value && *value)
				{
					value = ft_strtrim(value);
					ft_lstappend_token(head, ft_get_tokenid(value, 1), value);
				}
				value2 = ft_strsub(command + i, 0, ft_strlen(seperators[seperators_index].token_value));
				if (value2 && *value2)
				{
					value2 = ft_strtrim(value2);
					ft_lstappend_token(head, ft_get_tokenid(value2, 1), value2);
				}
				i += ft_strlen(seperators[seperators_index].token_value);
				last_index = i;
				break;
			}
			seperators_index++;
		}
		i++;
	}
	if (*(command + last_index))
	{
		value = ft_strtrim(command + last_index);
		ft_lstappend_token(head, ft_get_tokenid(value, 1), value);
	}
}