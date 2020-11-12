/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 15:15:48 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/12 18:55:29 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/to_sh_rl.h"

int			ft_readline()
{
	t_hist	*his;
	char	*line;

	tcgetattr(0, &g_saved_attributes);
	his = open_hist();
	line = ft_strdup("hi");
	if (!term_set() && line && ft_strcmp(line, "exit"))
	{
		ft_strdel(&line);
		line = get_line(&his, NULL, 1);
		write(1, "\n", 1);
		printf("%s\n", line);
		add_to_history(&his, line);
	}
	return (0);
}
