/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_in_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:56:41 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/19 19:10:38 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/readline.h"

void		add_in_pos(t_line *line)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = ft_strnew(ft_strlen(line->str) + 1);
	while (i < (size_t)line->idx)
	{
		tmp[i] = line->str[i];
		i++;
	}
	tmp[i] = line->buf;
	i++;
	while (i < ft_strlen((line->str)) + 1)
	{
		tmp[i] = line->str[i - 1];
		i++;
	}
	tmp[i] = '\0';
	ft_strdel(&(line->str));
	line->str = tmp;
	put_in_pos(line->str + line->idx);
	go_right(line);
}

void		del_in_pos(t_line *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	go_left(line);
	tmp = ft_strnew(ft_strlen(line->str) - 1);
	while (line->str[i])
	{
		if (i != line->idx)
		{
			tmp[j] = line->str[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	ft_strdel(&(line->str));
	line->str = tmp;
	put_in_pos(line->str + line->idx);
}

int			edit_in_pos(t_line *line)
{
	if (ft_isprint(line->buf))
		add_in_pos(line);
	else if (line->buf == BACKSPACE && line->idx)
		del_in_pos(line);
	else
		return (0);
	return (1);
}
