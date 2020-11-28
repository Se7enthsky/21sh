/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:10:14 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/26 02:25:22 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

/*
**  Seperators for the full command, coming directly from user input.
**  Example of full command :
**  "echo "foo" >> bar | pwd cat -e << EOF && ls -l dir1 dir2"
*/

static const t_id	g_seperators[] =
{
	{"&&", DGREAT, "Dgreat"},
	{"||", OR, "OR"},
	{"|", PIPE, "Pipe"},
	{";", SEMI, "Semi"},
	{NULL, 0, NULL},
};

char				**ft_envinit(void)
{
	char			**new_env;
	size_t			size;
	unsigned int	i;
	extern char		**environ;

	g_exit_code = 0;
	i = 0;
	size = ft_arraysize(environ);
	if ((new_env = malloc(sizeof(char *) * size + 1)) == NULL)
		exit(ENOMEM);
	while (i < size)
	{
		new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_ast				*ft_build_ast(char *cmd, char **env)
{
	t_ast		*root;
	t_tokens	*head;

	head = NULL;
	root = NULL;
	ft_stageone_tokenizer(&head, cmd, g_seperators);
	if (head)
	{
		ft_get_cmd(head, env);
		if ((root = ft_parse(head)) == NULL)
			return (NULL);
	}
	return (root);
}

void				init_prompt(void)
{
	char	**env;

	env = ft_envinit();
	ft_prompt(env);
	ft_free_arr(env);
}

int					main(void)
{
	signal(SIGINT, ft_sig_handler);
	init_prompt();
	return (0);
}
