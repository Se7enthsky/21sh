/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 21:09:19 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/20 10:49:36 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	putc_in_pos(char c)
{
	tputs(tgetstr("sc", NULL), 1, to_putchar);
	tputs(tgetstr("cd", NULL), 1, to_putchar);
	ft_putchar(c);
	tputs(tgetstr("rc", NULL), 1, to_putchar);
}

void	put_in_pos(char *str)
{
	tputs(tgetstr("sc", NULL), 1, to_putchar);
	tputs(tgetstr("cd", NULL), 1, to_putchar);
	ft_putstr(str);
	tputs(tgetstr("rc", NULL), 1, to_putchar);
}

int		prv_end(t_line *line)
{
	int		n;
	int		i;

	i = line->idx - 1;
	while (i >= 0 && line->str[i] != '\n')
		i--;
	n = line->idx - i;
	if (i < 0)
		n += line->prm;
	return (n % line->col);
}
