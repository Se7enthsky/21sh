/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:24:00 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/26 18:38:17 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static char		*get_trimmed_line(void)
{
	char	*command;
	char	*temp;

	command = readline("21sh> ");
	if (*command == 3)
	{
		g_exit_code = 1;
		return (NULL);
	}
	temp = ft_strtrim(command);
	ft_memdel((void**)&command);
	if (*temp == 3)
	{
		g_exit_code = 1;
		return (NULL);
	}
	return (temp);
}

void			ft_prompt(char **env)
{
	char		*cmd;
	t_ast		*root;
	int			pid;

	while (1)
	{
		if ((cmd = get_trimmed_line()) && *cmd)
		{
			write(1, "\n", 1);
			if ((root = ft_build_ast(cmd, env)) == NULL)
				ft_putendl_fd("21sh: parse error", 2);
			else
			{
				if (ft_find_heredoc(root, 0) == 0)
				{
					setup_files(root);
					ft_reset(ft_trav_exec(root, &env));
				}
				ft_free_ast(&root);
				ft_memdel((void **)&cmd);
			}
		}
		else
			ft_putchar('\n');
	}
}
