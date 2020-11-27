/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:50:56 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/27 20:52:03 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static char	*ft_strcdup(char c)
{
	char	*ret;

	ret = ft_strnew(2);
	ret[0] = c;
	return (ret);
}

char		*ret_line(char *prm, t_line line)
{
	char	*ret;

	if (line.buf == 3)
		ret = ft_strcdup(3);
	else if (line.buf == '\004' && !line.str[0] && !prm)
	{
		reset_input_mode();
		write(1, "\n", 1);
		exit(0);
	}
	else if (line.buf == '\004' && !line.str[0] &&
			!ft_strcmp(prm, "heredoc> "))
		ret = ft_strdup("\004");
	else
	{
		end(&line);
		ret = ft_strdup(line.str);
	}
	return (ret);
}
