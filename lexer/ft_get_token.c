#include "tokenize.h"

static const t_id	tokens[] = 
{
	{"|", PIPE, "pipe"},
	{"||", OR, "or"},
	{"&&", AND, "and"},
	{";", SEMI, "semi"},
	{"<", LESS, "less"},
	{"<<", DLESS, "dless"},
	{">", GREAT, "great"},
	{">>", DGREAT, "dgreat"},
	{"\"", DQ_STRING, "Double quoted string"},
	{"\'", SQ_STRING, "Single quoted string"},
};

char	*ft_get_tokenname(int token_id)
{
	int		i;

	i = 0;
	while (i < 10)
	{
		if (tokens[i].id == token_id)
			return (tokens[i].name);
		i++;
	}
	return (ft_strdup("full_command"));
}

int		ft_get_tokenid(char *token_value)
{
	int		i;

	i = 0;
	while (i < 10)
	{
		if (ft_strcmp(token_value, tokens[i].token_value) == 0)
			return (tokens[i].id);
		i++;
	}
	return (1);
}