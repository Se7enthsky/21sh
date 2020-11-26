/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:05:47 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/26 00:55:19 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	ft_join_heredoc(char *line, char **doc_str)
{
	char	*temp2;
	char	*temp;

	temp2 = ft_strjoin(line, "\n");
	temp = ft_strjoin(*doc_str, temp2);
	ft_memdel((void**)&temp2);
	ft_memdel((void**)doc_str);
	*doc_str = temp;
}

char	*ft_heredoc_prompt(char *delimiter, t_hist *his)
{
	char	*line;
	char	*doc_str;

	doc_str = ft_strdup("");
	while (1)
	{
		if ((line = get_line(&his, "heredoc> ", 1)))
		{
			write(1, "\n", 1);
			if (*line == 3 || !ft_strcmp(delimiter, line) || line[0] == '\004')
			{
				ft_memdel((void**)&line);
				if (*line == 3)
					ft_memdel((void**)&doc_str);
				break ;
			}
			else
				ft_join_heredoc(line, &doc_str);
		}
		else
			ft_putchar('\n');
	}
	return (doc_str);
}

int		ft_parse_heredoc(t_tokens *head)
{
	char		*delimiter;
	char		*here_doc;
	t_hist		*his;

	his = open_hist();
	while (head)
	{
		if (head->next && head->next->token_id == DLESS)
		{
			if (head->next->next)
				delimiter = head->next->next->value;
			here_doc = ft_heredoc_prompt(delimiter, his);
			if (here_doc == NULL)
			{
				free_his(&his);
				return (1);
			}
			head->next->heredoc = here_doc;
		}
		head = head->next;
	}
	free_his(&his);
	return (0);
}

int		ft_find_heredoc(t_ast *root, int c)
{
	if (root == NULL || c == 1)
		return (c);
	c = ft_find_heredoc(root->left, c);
	if (root->token->token_id == SIMPLE_COMMAND || c == 0)
		c = ft_parse_heredoc(root->token->command_tokens);
	c = ft_find_heredoc(root->right, c);
	return (c);
}
