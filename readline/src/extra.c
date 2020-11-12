/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 23:34:31 by aminewalial       #+#    #+#             */
/*   Updated: 2020/02/25 14:39:49 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/to_sh_rl.h"

char	*char_join(char *str, int c)
{
	char	*ret;
	int		i;

	ret = ft_strnew(ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = c;
	return (ret);
}

int		to_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int		to_putstr(char *s)
{
	int		i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar(s[i]);
			i++;
		}
	}
	return (i);
}

void	free_2d(char ***dar)
{
	int		i;

	i = 0;
	if (dar)
		while ((*dar)[i])
		{
			ft_strdel(&(*dar)[i]);
			i++;
		}
	free(*dar);
	*dar = NULL;
}

int		is_ws(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}
