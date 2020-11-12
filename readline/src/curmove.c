/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 20:46:12 by awali-al          #+#    #+#             */
/*   Updated: 2020/02/25 14:39:49 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/to_sh_rl.h"

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
