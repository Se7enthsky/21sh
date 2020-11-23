/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:17:39 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/23 20:17:52 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void				ft_sig_handler(int signo)
{
	(void)signo;
	if (g_pid == 0)
	{
		if (g_line.str)
		{
			g_line.str[0] = '\0';
			g_line.len = 0;
			g_line.idx = 0;
			g_line.way = 0;
		}
		ft_putendl("");
		display_prompt(1);
	}
}
