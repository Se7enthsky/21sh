/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:41:17 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/19 19:09:55 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/readline.h"

void		go_right(t_line *line)
{
	int		i;
	int		n;

	i = lines_in_cmd(line->str + line->idx, line->curp.col - 1, line->col);
	n = line->row - line->curp.row + 1;
	if (line->str[line->idx] == '\n' || line->col == line->curp.col)
	{
		cur_down(line);
		cur_begn(line);
	}
	else
	{
		if (i > n)
			cur_upln(line);
		cur_rght(line);
	}
	line->idx++;
}

void		go_left(t_line *line)
{
	line->idx--;
	if (line->curp.col > 1)
		cur_left(line);
	else
	{
		cur_upln(line);
		if (line->str[line->idx] == '\n')
			line->curp.col = prv_end(line);
		else
			line->curp.col = line->col;
		tputs(tgoto(tgetstr("ch", NULL), 0, line->curp.col - 1), 1, to_putchar);
	}
}

static void	go_up(t_line *line)
{
	int		n;
	int		i;

	i = 0;
	n = line->curp.col;
	if (line->str[line->idx] == '\n')
	{
		go_left(line);
		i++;
	}
	while (line->idx && line->str[line->idx] != '\n' && i++ < line->col)
		go_left(line);
	while (line->idx && line->curp.col > n)
		go_left(line);
}

static void	go_down(t_line *line)
{
	int		n;
	int		i;

	i = 0;
	n = line->col - line->curp.col;
	while (line->str[line->idx] && line->str[line->idx - 1] != '\n' &&
			i++ < line->col)
		go_right(line);
	if (i < n)
	{
		n = line->col - n - 1;
		i = 0;
		while (line->str[line->idx] && line->str[line->idx] != '\n' && i++ < n)
			go_right(line);
	}
}

int			arrow_movement(t_line *line)
{
	if (line->buf == RGHT && line->idx < (int)ft_strlen(line->str))
		go_right(line);
	else if (line->buf == LEFT && line->idx)
		go_left(line);
	else if (line->buf == ALT_UPAR)
		go_up(line);
	else if (line->buf == ALT_DOWN)
		go_down(line);
	else
		return (0);
	return (1);
}
