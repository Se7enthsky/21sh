#include "tokenize.h"

/*
 * Seperators for complete command. 
 */

// static const t_id		token_seperators[] =
// {
// 	{"|", PIPE, "pipe"},
// 	{"||", OR, "or"},
// 	{"&&", AND, "and"},
// 	{";", SEMI, "semi"}
// };


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


void    ft_tokenize(t_tokens **head, char *command)
{
    char    *seperators[] = {"&&", "||", ";", "|", NULL};
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
		while (seperators[seperators_index])
		{
			if (ft_strequ(command + i, seperators[seperators_index]))
			{
				value = ft_strsub(command, last_index, i - last_index);
				if (value && *value)
				{
					value = ft_strtrim(value);
					ft_lstappend_token(head, ft_get_tokenid(value), value);
				}
				value2 = ft_strsub(command + i, 0, ft_strlen(seperators[seperators_index]));
				if (value2 && *value2)
				{
					value2 = ft_strtrim(value2);
					ft_lstappend_token(head, ft_get_tokenid(value2), value2);
				}
				i += ft_strlen(seperators[seperators_index]);
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
		ft_lstappend_token(head, ft_get_tokenid(value), value);
	}
}