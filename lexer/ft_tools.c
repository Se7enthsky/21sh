#include "tokenize.h"

/*
 * Tokens
 */

static const t_id tokens[] =
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
		if (tokens[i].id == id)
			return (ft_strdup(tokens[i].name));
		i++;
	}
	return (ft_strdup("SIMPLE_COMMAND"));
}

int		ft_get_tokenid(const char *value, int id)
{
	unsigned int i;

	i = 0;
	if (ft_strlen(value) >= 2)
	{
		if (ft_isdigit(*value) && *(value + 1) == '>')
			return (FD_AGR);
	}
	while (i < 8)
	{
		if (ft_strcmp(tokens[i].token_value, value) == 0)
			return (tokens[i].id);
		i++;
	}
	return (id);
}