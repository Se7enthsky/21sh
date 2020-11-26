/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:50:56 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/26 00:36:58 by mobounya         ###   ########.fr       */
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
		exit(0);
	else if (line.buf == '\004' && !g_l.str[0] &&
			!ft_strcmp(prm, "heredoc> "))
		ret = ft_strdup("\004");
	else
		ret = ft_strdup(g_l.str);
	return (ret);
}
