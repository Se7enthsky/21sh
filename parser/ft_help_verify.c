/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help_verify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:43:24 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/20 10:50:30 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int		starter_ids(int alt[])
{
	int		i;

	alt[0] = SIMPLE_COMMAND;
	alt[1] = WORD;
	alt[2] = SQ_STRING;
	alt[3] = DQ_STRING;
	alt[4] = FD_LESS_AGR;
	alt[5] = FD_GREAT_AGR;
	alt[6] = FD_FILE;
	alt[7] = FD_GREAT;
	i = 8;
	return (i);
}

int		seperators_id(int alt[])
{
	int		i;

	alt[0] = PIPE;
	alt[1] = OR;
	alt[2] = AND;
	alt[3] = SEMI;
	i = 4;
	return (i);
}

int		function(int alt[])
{
	int		i;

	alt[0] = LESS;
	alt[1] = DLESS;
	alt[2] = GREAT;
	alt[3] = DGREAT;
	alt[4] = WORD;
	alt[5] = SQ_STRING;
	alt[6] = DQ_STRING;
	alt[7] = FD_GREAT_AGR;
	alt[8] = FD_LESS_AGR;
	alt[9] = SEMI;
	alt[10] = FD_GREAT;
	alt[11] = FD_FILE;
	i = 12;
	return (i);
}

void	ft_get_alernative_ids(int token_id, int alt[], int size)
{
	int	i;

	i = 0;
	if (token_id == -1)
		i = starter_ids(alt);
	if (token_id == SIMPLE_COMMAND)
		i = seperators_id(alt);
	else if (token_id >= 2 && token_id <= 6)
	{
		alt[0] = SIMPLE_COMMAND;
		i = 1;
	}
	else if (token_id >= 7 && token_id <= 11)
	{
		alt[0] = (token_id == DLESS) ? DELIMITER : FILENAME;
		i = 1;
	}
	else if (token_id >= 12 && token_id <= 19)
		i = function(alt);
	while (i < size)
		alt[i++] = 0;
}

int		ft_compare_token(int token_id, int alt[])
{
	unsigned int	i;

	i = 0;
	while (i < ARRAY_SIZE)
	{
		if (token_id == alt[i])
			return (1);
		i++;
	}
	return (0);
}
