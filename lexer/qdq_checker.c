/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qdq_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:31:28 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/20 16:54:48 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	re_cmd(t_hist *his, char **cmd, char x)
{
	char	*tmp;
	char	*line;
	int		ret;
	
	tmp = ft_strjoin(*cmd, "\n");
	ret = ft_strlen(*cmd);
	ft_strdel(cmd);
	write(1, "\n", 1);
	if (x == '\'')
		line = get_line(&his, "quote> ", 1);
	else if (x == '\"')
		line = get_line(&his, "dquote> ", 1);
	*cmd = ft_strjoin(tmp, line);
	ft_strdel(&tmp);
	ft_strdel(&line);
	return (ret);
}

void		qdq_checker(char **cmd)
{
	t_hist	*his;
	char	x;
	int		i;

	i = 0;
	x = '\0';
	his = open_hist();
	while ((*cmd)[i] || x)
	{
		if (x && !(*cmd)[i])
			re_cmd(his, cmd, x);
		else if (((*cmd)[i] == '\'' || (*cmd)[i] == '\"') && !x)
		{
			i = ft_strchri(*cmd + i + 1, (x = (*cmd)[i]));
			if (i == -1)
				i = re_cmd(his, cmd, x);
			else
				x = '\0';
		}
		else if (x && (*cmd)[i] == x)
			x = '\0';
		i++;
	}
}
