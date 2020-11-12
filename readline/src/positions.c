/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 21:09:19 by awali-al          #+#    #+#             */
/*   Updated: 2020/02/26 20:05:12 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/to_sh_rl.h"

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
