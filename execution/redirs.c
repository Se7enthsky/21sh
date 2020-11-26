/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:43:04 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/26 04:13:55 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

#define READING 1
#define WRITING 2

void	ft_fdagr(char *value)
{
	int old_fd;
	int new_fd;

	new_fd = value[0] - '0';
	if (value[3] == '-')
		close(new_fd);
	else
	{
		old_fd = value[3] - '0';
		dup2(old_fd, new_fd);
	}
}

void	ft_fd_to_file(char *value)
{
	int		old_fd;
	char	*filename;
	int		oflag;

	old_fd = value[0] - '0';
	filename = ft_strdup(value + 2);
	if (filename == NULL)
		exit(ENOMEM);
	oflag = O_TRUNC | O_WRONLY | O_CREAT;
	ft_redirect_to_file(oflag, old_fd, filename, WRITING);
	free(filename);
}

void	ft_heredoc(char *value)
{
	int		fd;
	char	*doc_file;

	doc_file = ft_strjoin("/tmp", "/.temp");
	fd = open(doc_file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	write(fd, value, ft_strlen(value));
	close(fd);
	ft_redirect_to_file(O_RDONLY, STDIN_FILENO, doc_file, READING);
}

int		ft_set_redirs(t_tokens *lst)
{
	while (lst)
	{
		if ((lst->token_id == GREAT) || (lst->token_id == DGREAT))
		{
			if (lst->token_id == GREAT)
				ft_redirect_to_file(O_TRUNC | O_WRONLY | O_CREAT,
									1, lst->next->value, WRITING);
			else if (lst->token_id == DGREAT)
				ft_redirect_to_file(O_WRONLY | O_APPEND | O_CREAT,
									1, lst->next->value, WRITING);
		}
		else if (lst->token_id == FD_GREAT_AGR || lst->token_id == FD_LESS_AGR)
			ft_fdagr(lst->value);
		else if (lst->token_id == FD_FILE)
			ft_fd_to_file(lst->value);
		else if (lst->token_id == FD_GREAT)
			ft_redirect_to_file(O_TRUNC | O_WRONLY | O_CREAT,
								lst->value[0] - 48, lst->next->value, WRITING);
		else if (lst->token_id == DLESS)
			ft_heredoc(lst->heredoc);
		else if (lst->token_id == LESS)
			ft_redirect_to_file(O_RDONLY, 0, lst->next->value, READING);
		lst = lst->next;
	}
	return (0);
}
