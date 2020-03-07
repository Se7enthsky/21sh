#include "tokenize.h"

int		ft_strchri(const char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

void	ft_tokenize(t_tokens **head, char *command, const t_id separators[])
{
	int		i;
	int		separators_index;
	int		last_index;
	char	*value;
	char	*value2;

	i = 0;
	last_index = 0;
	while (command[i])
	{
		separators_index = 0;
		if (command[i] == '\"' || command[i] == '\'')
		{
			i += ft_strchri(command + i + 1, command[i]) + 1;
			i = i + 1;
		}
		while (separators[separators_index].token_value)
		{
			if (ft_strncmp(command + i, separators[separators_index].token_value, ft_strlen(separators[separators_index].token_value)) == 0)
			{
				value = ft_strsub(command, last_index, i - last_index);
				value = ft_strtrim(value);
				if (value && *value)
					ft_lstappend_token(head, ft_get_tokenid(value, 1), value);
				value2 = ft_strsub(command, i, ft_strlen(separators[separators_index].token_value));
				if (value2 && *value2)
				{
					value2 = ft_strtrim(value2);
					ft_lstappend_token(head, ft_get_tokenid(value2, 1), value2);
				}
				i += ft_strlen(separators[separators_index].token_value);
				last_index = i;
				break ;
			}
			separators_index++;
		}
		i += command[i] != '\0';
	}
	if (*(command + last_index))
	{
		value = ft_strtrim(command + last_index);
		if (value && *value)
			ft_lstappend_token(head, ft_get_tokenid(value, 1), value);
	}
}
