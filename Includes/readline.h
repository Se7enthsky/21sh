/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:40:20 by awali-al          #+#    #+#             */
/*   Updated: 2020/11/24 17:30:29 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <stdio.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <fcntl.h>

# include "../Libft/libft.h"

# define RED_COL		"\e[31m"
# define GRN_COL		"\e[32m"
# define RST_COL		"\e[37m"

# define SET_HGH		"\e[47m\e[30m"
# define RST_HGH		"\e[0m\e[37m"

# define ALT_UPAR		1096489755
# define ALT_DOWN		1113266971
# define ALT_RGHT		1130044187
# define ALT_LEFT		1146821403

# define ALT_UPLN		895163163
# define ALT_DNLN		911940379

# define PRV_WRD		10783202
# define NXT_WRD		10848738

# define PST			10127586
# define CUT			8948194
# define CPY			42947

# define BACKSPACE		127

# define UPAR			4283163
# define DOWN			4348699
# define LEFT			4479771
# define RGHT			4414235

# define HOME			4741915
# define END			4610843

# define SEPARATOR		(char)-1

typedef struct			s_pos
{
	int					row;
	int					col;
}						t_pos;

typedef struct			s_line
{
	t_pos				curp;
	char				*str;
	char				*tmp;
	char				*hgh;
	int					len;
	int					way;
	int					idx;
	int					buf;
	int					col;
	int					row;
	int					prm;
}						t_line;

typedef struct			s_hist
{
	struct s_hist		*prv;
	struct s_hist		*nxt;
	char				*cmd;
	int					i;
}						t_hist;

extern struct termios	g_saved_attributes;
extern char				*g_past;

char					*char_join(char *str, int c);
void					free_2d(char ***dar);
int						to_putstr(char *s);
int						to_putchar(int c);
int						is_ws(char c);

t_line					line_ini(char *prom, int c);

char					**my_envirenement(char **env);
char					*value_of(char **env, char *key);
int						term_set(void);

t_hist					*open_hist(void);
void					add_to_history(t_hist **his, char *line);

char					*get_line(t_hist **his, char *prom, int c);
int						display_prompt(int c);
void					reset_highlight(t_line *line);

void					set_input_mode(void);
void					reset_input_mode(void);

void					cur_begn(t_line *line);
void					cur_rght(t_line *line);
void					cur_left(t_line *line);
void					cur_upln(t_line *line);
void					cur_down(t_line *line);

void					putc_in_pos(char c);
void					put_in_pos(char *str);
int						prv_end(t_line *line);
int						lines_in_cmd(char *str, int prm, int col);

void					end(t_line *line);
void					home(t_line *line);
void					go_left(t_line *line);
void					go_right(t_line *line);

void					ccp(t_line *line);
int						highlight(t_line *line);
int						navigation(t_line *line);
int						edit_in_pos(t_line *line);
int						arrow_movement(t_line *line);
int						his_nav(t_hist **his, t_line *line);
t_pos					get_curpos(void);

int						my_type(char **line);
#endif
