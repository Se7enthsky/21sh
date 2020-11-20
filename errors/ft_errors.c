/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:15:00 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/20 10:52:10 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void		ft_errors(void)
{
	static char *errors[] = {
		"Undefined error: 0",
		"No such file or directory",
		"Too many arguments",
		"Permission denied",
		"Not a directory",
		NULL,
	};

	if (g_exit_code > 0 && g_exit_code <= 4)
		ft_putendl_fd(errors[g_exit_code], 2);
}
