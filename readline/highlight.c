/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   highlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:38:12 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/19 19:10:59 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/readline.h"

static void	put_with_hgh(t_line *line, int c)
{
	int		p;
	int		i;

	p = line->idx;
	while (line->str + line->idx > line->hgh)
		go_left(line);
	if (c)
	{
		go_left(line);
		putc_in_pos(line->str[line->idx]);
		go_right(line);
	}
	i = 0;
	ft_putstr(SET_HGH);
	while (line->str[line->idx])
	{
		if (i++ == line->len)
			ft_putstr(RST_HGH);
		putc_in_pos(line->str[line->idx]);
		go_right(line);
	}
	ft_putstr(RST_HGH);
	tputs(tgetstr("cd", NULL), 1, to_putchar);
	while (line->idx > p)
		go_left(line);
}

static void	lefty(t_line *line)
{
	go_left(line);
	if (line->hgh)
	{
		if (line->way == -1)
		{
			line->hgh--;
			line->len++;
		}
		else
			line->len--;
	}
	else
	{
		line->hgh = line->str + line->idx;
		line->len = 1;
		line->way = -1;
	}
	if (!line->len)
		reset_highlight(line);
	else
		put_with_hgh(line, 0);
}

static void	righty(t_line *line)
{
	int		c;

	go_right(line);
	c = 0;
	if (line->hgh)
	{
		if (line->way == 1)
			line->len++;
		else
		{
			line->hgh++;
			line->len--;
			c++;
		}
	}
	else
	{
		line->hgh = line->str + line->idx - 1;
		line->len = 1;
		line->way = 1;
	}
	if (!line->len)
		reset_highlight(line);
	else
		put_with_hgh(line, c);
}

int			highlight(t_line *line)
{
	if (line->buf == ALT_LEFT && line->idx)
		lefty(line);
	else if (line->buf == ALT_RGHT && line->str[line->idx])
		righty(line);
	else
		return (0);
	return (1);
}
