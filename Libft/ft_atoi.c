/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 22:18:27 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/17 14:46:10 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Get the number of digits in a string
*/

static int	ft_strdig(const char *str)
{
	int digits;

	digits = 0;
	while (ft_isdigit(*str))
	{
		digits++;
		str++;
	}
	return (digits);
}

int			ft_atoi(const char *str)
{
	int neg;
	int integ;

	integ = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	neg = (*str == '-') ? 1 : 0;
	str += (*str == '-' || *str == '+') ? 1 : 0;
	if (ft_strdig(str) > 18)
		return ((neg == 1) ? 0 : -1);
	if (ft_strdig(str) == 18 && ft_strcmp(str, "9223372036854775807") > 0)
		return ((neg == 1) ? 0 : -1);
	while (*str != '\0')
	{
		if (ft_isdigit(*str))
		{
			integ *= 10;
			integ += (int)*str - 48;
		}
		else
			break ;
		str++;
	}
	return ((neg == 1) ? -integ : integ);
}
