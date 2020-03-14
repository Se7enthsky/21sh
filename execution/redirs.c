#include "execute.h"

int		ft_redirect_to_file(int oflag, int old_fd, char *filename)
{
	char	*path;
	int		new_fd;

	path = ft_strjoin("./", filename);
	new_fd = open(filename, oflag, S_IRWXU);
	if (new_fd == -1)
	{
		ft_putendl_fd("open failed", 2);
		return (1);
	}
	dup2(new_fd, old_fd);
	return (0);
}

void	ft_fdagr(char *value)
{
	int		old_fd;
	int		new_fd;

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

	old_fd = value[0] - '0';
	filename = ft_strdup(value + 2);
	if (filename == NULL)
		exit(ENOMEM);
	ft_redirect_to_file(O_TRUNC | O_WRONLY | O_CREAT, old_fd, filename);
	free(filename);
}

int		ft_set_redirs(t_tokens *lst)
{
	int		oflag;

	while (lst)
	{
		if ((lst->token_id == GREAT) || (lst->token_id == DGREAT))
		{
			if (lst->token_id == GREAT)
				oflag = O_TRUNC | O_WRONLY | O_CREAT;
			else if (lst->token_id == DGREAT)
				oflag = O_WRONLY | O_APPEND | O_CREAT;
			ft_redirect_to_file(oflag, 1, lst->next->value);
		}
		else if (lst->token_id == FD_AGR)
			ft_fdagr(lst->value);
		else if (lst->token_id == FD_FILE)
			ft_fd_to_file(lst->value);
		else if (lst->token_id == FD_GREAT)
			ft_redirect_to_file(O_TRUNC | O_WRONLY | O_CREAT, \
			lst->value[0], lst->next->value);
		else if (lst->token_id == LESS)
			ft_redirect_to_file(O_RDONLY, 0, lst->next->value);
		lst = lst->next;
	}
	return (0);
}