/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:51:10 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/26 01:47:18 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "tokenize.h"
# include "errors.h"
# include "execute.h"
# include "parser.h"
# include "readline.h"

t_line				g_l;
int					g_pid;

typedef struct		s_env
{
	char			**env;
	unsigned int	size;
}					t_env;

void				ft_get_cmd(t_tokens *head, char **env);
t_ast				*ft_parse(t_tokens *lst);
int					*ft_trav_exec(t_ast *root, char ***env);
int					ft_arraysize(char **ar);
void				ft_free_ast(t_ast **root);
void				free_his(t_hist **his);
void				setup_files(t_ast *root);
void				init_prompt(void);
void				ft_sig_handler(int signo);
void				setup_andor(t_ast *root, int *and_or);
void				ft_prompt(t_hist *his, char **env);
#endif
