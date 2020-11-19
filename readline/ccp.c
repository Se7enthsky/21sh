/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ccp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 01:36:11 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/19 19:10:08 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/readline.h"

static void	cpy(t_line *line)
{
	if (g_past)
		ft_strdel(&g_past);
	g_past = ft_strndup(line->hgh, line->len);
}

static void	cut(t_line *line)
{
	char	*tmp;
	char	*p1;

	cpy(line);
	while (line->str + line->idx > line->hgh)
		go_left(line);
	tmp = line->str;
	p1 = ft_strndup(line->str, line->idx);
	line->str = ft_strjoin(p1, line->hgh + line->len);
	ft_strdel(&tmp);
	ft_strdel(&p1);
	reset_highlight(line);
}

static void	pst(t_line *line)
{
	char	*tmp;
	char	*p1;
	char	*p2;
	int		i;

	tmp = line->str;
	p1 = ft_strndup(line->str, line->idx);
	p2 = ft_strjoin(g_past, line->str + line->idx);
	ft_strdel(&tmp);
	line->str = ft_strjoin(p1, p2);
	ft_strdel(&p1);
	ft_strdel(&p2);
	line->hgh = line->str;
	reset_highlight(line);
	i = ft_strlen(g_past);
	while (i--)
		go_right(line);
}

void		ccp(t_line *line)
{
	if (line->buf == CPY && line->hgh)
		cpy(line);
	else if (line->buf == CUT && line->hgh)
		cut(line);
	else if (line->buf == PST)
		pst(line);
}
