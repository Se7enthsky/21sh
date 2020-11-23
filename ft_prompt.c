/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:24:00 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/23 20:35:43 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static char		*get_trimmed_line(t_hist *his)
{
	char	*command;
	char	*temp;

	command = get_line(&his, NULL, g_exit_code);
	temp = ft_strtrim(command);
	ft_memdel((void**)&command);
	return (temp);
}

void			ft_prompt(t_hist *his, char **env)
{
	char		*cmd;
	t_ast		*root;

	if (!term_set())
		while (1)
		{
			if ((cmd = get_trimmed_line(his)) && *cmd)
			{
				qdq_checker(&his, &cmd);
				add_to_history(&his, cmd);
				write(1, "\n", 1);
				if ((root = ft_build_ast(cmd, env)) == NULL)
					ft_putendl_fd("21sh: parse error", 2);
				else
				{
					setup_files(root);
					ft_reset(ft_trav_exec(root, &env));
				}
				ft_free_ast(&root);
				ft_memdel((void **)&cmd);
			}
			else
				ft_putchar('\n');
		}
}
