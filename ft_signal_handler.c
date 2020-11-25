/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:17:39 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/25 17:53:30 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void				ft_sig_handler(int signo)
{
	(void)signo;
	if (g_pid == 0)
	{
		if (g_l.str)
		{
			g_l.str[0] = '\0';
			g_l.len = 0;
			g_l.idx = 0;
			g_l.way = 0;
		}
		ft_putendl("");
		display_prompt(1);
	}
}
