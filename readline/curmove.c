/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 20:46:12 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/20 10:50:08 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	cur_begn(t_line *line)
{
	tputs(tgetstr("cr", NULL), 1, to_putchar);
	line->curp.col = 1;
}

void	cur_left(t_line *line)
{
	tputs(tgetstr("le", NULL), 1, to_putchar);
	line->curp.col--;
}

void	cur_rght(t_line *line)
{
	tputs(tgetstr("nd", NULL), 1, to_putchar);
	line->curp.col++;
}

void	cur_upln(t_line *line)
{
	tputs(tgetstr("up", NULL), 1, to_putchar);
	if (line->curp.row)
		line->curp.row--;
}

void	cur_down(t_line *line)
{
	tputs(tgetstr("do", NULL), 1, to_putchar);
	if (line->curp.row < line->row)
		line->curp.row++;
}
