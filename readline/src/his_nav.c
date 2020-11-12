/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   his_nav.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 01:29:39 by aminewalial       #+#    #+#             */
/*   Updated: 2020/11/10 12:05:02 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/to_sh_rl.h"

int			lines_in_cmd(char *str, int prm, int col)
{
	int		i;
	int		c;

	i = 0;
	c = 1;
	while (str[i])
	{
		if (str[i] == '\n' || prm == col)
		{
			c++;
			prm = 1;
		}
		else
			prm++;
		i++;
	}
	return (c);
}

static void	prev_line(t_hist **his, t_line *line)
{
	int		n;
	int		i;

	n = lines_in_cmd(line->str, line->prm, line->col);
	if (*his)
	{
		home(line);
		if (!line->tmp)
			line->tmp = line->str;
		else if ((*his)->prv)
			(*his) = (*his)->prv;
		line->str = (*his)->cmd;
		put_in_pos(line->str);
		n = lines_in_cmd(line->str, line->prm, line->col) - n;
		i = line->row - line->curp.row;
		while (n-- > i)
			cur_upln(line);
		line->idx = 0;
		end(line);
	}
}

static void	next_line(t_hist **his, t_line *line)
{
	if (line->tmp)
	{
		home(line);
		if ((*his)->nxt)
		{
			(*his) = (*his)->nxt;
			line->str = (*his)->cmd;
		}
		else
		{
			line->str = line->tmp;
			line->tmp = NULL;
		}
		put_in_pos(line->str);
		end(line);
	}
}

int			his_nav(t_hist **his, t_line *line)
{
	if (line->buf == UPAR)
		prev_line(his, line);
	else if (line->buf == DOWN)
		next_line(his, line);
	else
		return (0);
	return (1);
}
