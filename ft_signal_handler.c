/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:17:39 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/26 02:23:37 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void				ft_sig_handler(int signo)
{
	(void)signo;
	if (g_pid == 0)
	{
		ft_putendl("");
		g_l = line_ini(NULL, 1);
	}
}
