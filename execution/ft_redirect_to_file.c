/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_to_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:22:04 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/23 17:41:07 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

#define READING 1
#define WRITING 2

static void		ft_permission_checker(int oflag, char *path, \
				char *filename, int rw)
{
	if (access(path, F_OK) == 0)
	{
		if (rw == WRITING && access(path, W_OK))
		{
			ft_putstr_fd(filename, 2);
			ft_putstr_fd(": ", 2);
			g_exit_code = 3;
		}
		else if (rw == READING && access(path, R_OK))
		{
			ft_putstr_fd(filename, 2);
			ft_putstr_fd(": ", 2);
			g_exit_code = 3;
		}
	}
	else if ((oflag | O_RDONLY) == 0)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		g_exit_code = 1;
	}
}

int				ft_redirect_to_file(int oflag, int old_fd, \
				char *filename, int rw)
{
	char	*path;
	int		new_fd;

	g_exit_code = 0;
	path = ((*filename == '.' || *filename == '/')) ? \
			ft_strdup(filename) : ft_strjoin("./", filename);
	ft_permission_checker(oflag, path, filename, rw);
	if (g_exit_code)
	{
		ft_memdel((void **)&path);
		return (g_exit_code);
	}
	new_fd = open(path, oflag, S_IRUSR | S_IWUSR);
	dup2(new_fd, old_fd);
	ft_memdel((void **)&path);
	close(new_fd);
	return (0);
}
