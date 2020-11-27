/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 13:46:50 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/27 21:06:19 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void			reset_highlight(t_line *line)
{
	int				i;

	if (line->hgh)
	{
		line->hgh = NULL;
		line->len = 0;
		line->way = 0;
		i = line->idx;
		home(line);
		put_in_pos(line->str);
		while (line->idx < i)
			go_right(line);
	}
}

static void		store_print(t_hist **his, t_line *line)
{
	if (edit_in_pos(line))
		reset_highlight(line);
	else if (arrow_movement(line))
		reset_highlight(line);
	else if (navigation(line))
		reset_highlight(line);
	else if (his_nav(his, line))
		reset_highlight(line);
	else if (highlight(line))
		g_past = ft_strnew(1);
	else if (g_past || line->hgh)
		ccp(line);
}

int				display_prompt(int c)
{
	char		*col;
	char		*path;
	static char	*tmp = NULL;

	if (!c)
		col = GRN_COL;
	else
		col = RED_COL;
	path = getcwd(NULL, 0);
	if (path)
	{
		ft_strdel(&tmp);
		tmp = ft_strrchr(path, '/');
		tmp = tmp && tmp[1] ? ft_strdup(tmp + 1) : ft_strdup(path);
		ft_strdel(&path);
	}
	ft_putstr(tmp);
	ft_putstr(col);
	ft_putstr(" $> ");
	ft_putstr(RST_COL);
	return (ft_strlen(tmp) + 4);
}

t_line			line_ini(char *prom, int c)
{
	struct winsize	ws;
	t_line			ret;

	ret.prm = prom ? to_putstr(prom) : display_prompt(c);
	ioctl(0, TIOCGWINSZ, &ws);
	ret.curp = get_curpos();
	ret.str = ft_strnew(1);
	ret.col = ws.ws_col;
	ret.row = ws.ws_row;
	ret.tmp = NULL;
	ret.hgh = NULL;
	ret.len = 0;
	ret.way = 0;
	ret.idx = 0;
	return (ret);
}

char			*get_line(t_hist **his, char *prm, int c)
{
	char			*ret;

	set_input_mode();
	g_l = line_ini(prm, c);
	while (1)
	{
		g_l.buf = 0;
		read(0, &g_l.buf, 12);
		if ((g_l.buf != '\n' && g_l.buf != '\004' && g_l.buf != 3) ||
				(g_l.buf == '\004' && g_l.idx != (int)ft_strlen(g_l.str)))
			store_print(his, &g_l);
		else if (g_l.buf == 3 || g_l.buf == '\n' || (g_l.buf == '\004' &&
				!g_l.str[0] && (!prm || !ft_strcmp(prm, "heredoc> "))))
			break ;
	}
	ret = ret_line(prm, g_l);
	ft_strdel(&g_l.str);
	reset_input_mode();
	return (ret);
}
