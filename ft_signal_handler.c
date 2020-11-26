/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:17:39 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/25 20:49:50 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void				ft_sig_handler(int signo)
{
	(void)signo;
	if (g_pid == 0)
	{
		g_con = 1;
		ft_putendl("");
		ft_putstr("$");
		g_l = line_ini(NULL, 1);
		ft_putstr("%");
	}
}
