/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:33:04 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/19 19:11:07 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/readline.h"

static t_hist	*new_node(char *str)
{
	t_hist	*ret;

	if (str && *str)
	{
		ret = (t_hist*)malloc(sizeof(t_hist));
		ret->cmd = ft_strdup(str);
		ret->prv = NULL;
		ret->nxt = NULL;
		return (ret);
	}
	else
		return (NULL);
}

static void		file_save(t_hist *his, char *str)
{
	char	*idx;
	char	*tmp;
	int		fd;

	idx = ft_strjoin(getenv("HOME"), "/.history");
	fd = open(idx, O_WRONLY | O_APPEND);
	ft_strdel(&idx);
	if (his)
		tmp = ft_itoa(his->i + 1);
	else
		tmp = ft_itoa(1);
	idx = char_join(tmp, ' ');
	ft_strdel(&tmp);
	tmp = ft_strjoin(idx, str);
	ft_strdel(&idx);
	idx = char_join(tmp, SEPARATOR);
	ft_strdel(&tmp);
	write(fd, idx, ft_strlen(idx));
	ft_strdel(&idx);
	close(fd);
}

void			add_to_history(t_hist **his, char *line)
{
	t_hist	*node;
	int		c;

	if (line)
	{
		c = 1;
		while ((*his) && (*his)->nxt)
			*his = (*his)->nxt;
		if (*his && !ft_strcmp(line, (*his)->cmd))
			c = 0;
		if (line && line[0] && c)
		{
			file_save(*his, line);
			node = new_node(line);
			if (*his)
			{
				node->i = (*his)->i + 1;
				node->prv = *his;
				(*his)->nxt = node;
			}
			else
				node->i = 1;
			*his = node;
		}
	}
}

static char		*next_cmd(int fd)
{
	char	*ret;
	char	*tmp;
	char	buf[2];
	int		rd;

	ret = ft_strnew(1);
	if (read(fd, buf, 0) == -1)
		return (NULL);
	while ((rd = read(fd, buf, 1)) && buf[0] != SEPARATOR)
	{
		buf[1] = '\0';
		tmp = ret;
		ret = ft_strjoin(tmp, buf);
		ft_strdel(&tmp);
	}
	if (!rd)
		return (NULL);
	return (ret);
}

t_hist			*open_hist(void)
{
	t_hist	*ret;
	char	*str;
	int		fd;

	str = ft_strjoin(getenv("HOME"), "/.history");
	fd = open(str, O_RDONLY | O_CREAT, S_IRWXU);
	ft_strdel(&str);
	str = next_cmd(fd);
	ret = NULL;
	if (str && str[0])
	{
		ret = new_node(ft_strchr(str, ' ') + 1);
		ret ? ret->i = ft_atoi(str) : 0;
		ft_strdel(&str);
		while (ret && (str = next_cmd(fd)))
		{
			ret->nxt = new_node(ft_strchr(str, ' ') + 1);
			ret->nxt->i = ft_atoi(str);
			ret->nxt->prv = ret;
			ret = ret->nxt;
			ft_strdel(&str);
		}
	}
	close(fd);
	return (ret);
}
