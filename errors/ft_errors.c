/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:15:00 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/11 13:15:06 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

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
