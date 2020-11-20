/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_curpos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 18:24:04 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/20 10:49:54 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_pos	get_curpos(void)
{
	t_pos	ret;
	char	buf[30];
	int		c;
	int		i;

	ret.col = 0;
	ret.row = 0;
	c = 0;
	i = 0;
	write(1, "\033[6n", 4);
	while (c != 'R')
	{
		read(0, &c, 1);
		buf[i] = c;
		i++;
	}
	buf[i] = '\0';
	ret.col = ft_atoi(ft_strchr(buf, ';') + 1);
	ret.row = ft_atoi(buf + 2);
	return (ret);
}
