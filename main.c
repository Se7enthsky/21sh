/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:10:14 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/23 18:57:53 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"
#include <sys/errno.h>
#include <unistd.h>

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

void				ft_prompt(t_hist *his)
{
	char		*cmd;
	t_tokens	*head;
	t_ast		*root;
	char		**env;
	char		*temp;
	int			*and_or;

	env = ft_envinit();
	if (!term_set())
	{
		while (1)
		{
			cmd = get_line(&his, NULL, g_exit_code);
			temp = cmd;
			cmd = ft_strtrim(cmd);
			if (cmd && *cmd)
			{
				qdq_checker(&his, &cmd);
				add_to_history(&his, cmd);
				write(1, "\n", 1);
				if ((root = ft_build_ast(cmd, env)) == NULL)
					ft_putendl_fd("21sh: parse error", 2);
				else
				{
					setup_files(root);
					and_or = ft_trav_exec(root, &env);
					ft_reset(and_or);
				}
				ft_free_ast(&root);
				head = NULL;
				ft_memdel((void **)&cmd);
			}
			else
			{
				g_exit_code = 0;
				ft_putchar('\n');
			}
		}
		ft_free_arr(env);
	}
}

void				ft_sig_handler(int signo)
{
	(void)signo;
	if (g_pid == 0)
	{
		if (g_line.str)
		{
			g_line.str[0] = '\0';
			g_line.len = 0;
			g_line.idx = 0;
			g_line.way = 0;
		}
		ft_putendl("");
		display_prompt(1);
	}
}

void				init_prompt(void)
{
	t_hist *his;

	tcgetattr(0, &g_saved_attributes);
	his = open_hist();
	ft_prompt(his);
	free_his(&his);
}

int					main(void)
{
	signal(SIGINT, ft_sig_handler);
	g_pid = 0;
	init_prompt();
	return (0);
}
