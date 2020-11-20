/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:44:40 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/20 10:49:28 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char *g_past;
struct termios g_saved_attributes;

void	reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_saved_attributes);
}

void	set_input_mode(void)
{
	struct termios	tattr;
	char			*term_type;
	int				ret;

	term_type = getenv("TERM");
	ret = tgetent(0, term_type);
	tcgetattr(0, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &tattr);
}

int		term_set(void)
{
	char			*term_type;
	int				ret;

	g_past = NULL;
	if (!(term_type = getenv("TERM")))
	{
		ft_putendl_fd("TERM is not set.", 2);
		return (-1);
	}
	if ((ret = tgetent(NULL, term_type)) == -1)
	{
		ft_putendl_fd("Could not access to the termcap database.", 2);
		return (-1);
	}
	else if (!ret)
	{
		ft_putstr_fd("Terminal type: ", 2);
		ft_putstr_fd(term_type, 2);
		ft_putendl_fd(" is not defined in termcap database.", 2);
		return (-1);
	}
	return (0);
}
