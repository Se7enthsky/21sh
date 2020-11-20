/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 02:02:23 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/20 13:11:47 by mobounya         ###   ########.fr       */
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

char	**ft_envinit(void)
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

t_ast	*ft_build_ast(char *cmd, char **env)
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

void	ft_prompt(t_hist *his, char **env)
{
	char		*cmd;
	t_tokens	*head;
	t_ast		*root;

	if (!term_set())
	{
		while (1)
		{
			if ((cmd = get_line(&his, NULL, 1)) && *cmd)
			{
				
				write(1, "\n", 1);
				if ((root = ft_build_ast(cmd, env)) == NULL)
					ft_putendl_fd("21sh: parse error", 2);
				else
					ft_trav_exec(root, &env);
				ft_free_ast(&root);
				head = NULL;
				ft_memdel((void **)&cmd);
			}
			else
				ft_putchar('\n');
		}
		ft_free_arr(env);
	}
}

void	init_prompt(void)
{
	t_hist		*his;
	char		**env;

	env = ft_envinit();
	tcgetattr(0, &g_saved_attributes);
	his = open_hist();
	ft_prompt(his, env);
}

void	ft_sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		init_prompt();
	}
}

int		main(void)
{
	// signal(SIGINT, ft_sig_handler);
	init_prompt();
	return (0);
}
