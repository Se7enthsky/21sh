# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/05 14:26:42 by aminewalial       #+#    #+#              #
#    Updated: 2020/11/19 19:37:31 by awali-al         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

˜NAME = 21sh

FLAGS = -g -Wall -Wextra -Werror -ltermcap

SRC_DIR = .

OBJ_DIR = .obj

HDR_DIR = Includes

ERR_DIR = errors

EXC_DIR = execution

LEX_DIR = lexer

LNL_DIR = linked_lists

PRS_DIR = parser

RDL_DIR = readline

SRC_FILES = $(ERR_FILES) $(EXC_FILES) $(LEX_FILES) $(LNL_FILES) $(PRS_FILES) \
$(RDL_FILES) main.c ft_freemem.c

HDR_FILES = errors.h execute.h main.h parser.h readline.h to_sh.h tokenize.h

ERR_FILES = ft_errors.c

EXC_FILES = ft_builtins.c ft_env_func.c ft_env_helpers.c ft_execute.c redirs.c \
ft_execute_helpers.c ft_list_to_array.c ft_pipe.c ft_process.c ft_unsetenv.c

LEX_FILES = ft_file.c ft_stageone_tokenizer.c ft_stagetwo_tokenizer.c \
ft_tools.c ft_varsub.c

LNL_FILES = t_tokens.c

PRS_FILES = ft_help_verify.c ft_heredoc.c ft_new_astnode.c ft_parse.c \
ft_reset.c ft_verify_syntx.c

RDL_FILES = envirenement.c get_line.c term_set.c edit_in_pos.c \
arrow_movement.c navigation.c extra.c his_nav.c history.c curmove.c ccp.c \
positions.c highlight.c my_type.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

HDR = $(addprefix $(HDR_DIR)/, HDR_FILES)

ERR = $(addprefix $(ERR_DIR)/, ERR_FILES)

EXC = $(addprefix $(EXC_DIR)/, EXC_FILES)

LEX = $(addprefix $(LEX_DIR)/, LEX_FILES)

LNL = $(addprefix $(LNL_DIR)/, LNL_FILES)

PRS = $(addprefix $(PRS_DIR)/, PRS_FILES)

RDL = $(addprefix $(RDL_DIR)/, RDL_FILES)

LIB = Libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ) $(HDR)
	make -C libft/
	gcc $(FLAGS) -I $(HDR) $(OBJ) $(LIB) -o $(NAME) -ltermcap

$(OBJ) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(FLAGS) -c $< -I $(HDR) -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
	
clean :
	make -C libft/ clean
	/bin/rm -rf $(OBJ_DIR)

fclean : clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re : fclean all