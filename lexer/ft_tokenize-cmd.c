#include "tokenize.h"

static const t_id		seperators[] =
{
	{"|", PIPE, "pipe"},
	{"||", OR, "or"},
	{"&&", AND, "and"},
	{";", SEMI, "point"}
};


