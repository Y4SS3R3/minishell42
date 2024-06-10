# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 09:40:06 by mzouine           #+#    #+#              #
#    Updated: 2024/06/10 11:13:00 by ymassiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = parsing/env_parse.c \
		parsing/mz_lexer.c \
		parsing/ft_list.c \
		parsing/mz_make_cmd.c \
		parsing/lexer_utils1.c \
		parsing/mz_make_special.c\
		parsing/lexer_utils2.c \
		parsing/mz_parser.c \
		parsing/mz_checker.c \
		parsing/mz_last_scan.c\
		parsing/mz_split.c \
		parsing/mz_arr.c \
		execution/exec/operands.c \
		execution/exec/pipeline.c \
		execution/gc/gc_utils.c \
		execution/general_utils/lst_manu.c \
		execution/general_utils/utils1.c \
		execution/general_utils/utils2.c \
		minishell.c \
		execution/general_utils/plus.c \
		execution/tree/redir_utils1.c \
		execution/tree/tree.c \
		execution/exec/env.c \
		execution/general_utils/utils3.c \
		execution/exec/cmd_path.c \
		execution/exec/exec_utils1.c

OBJS = $(SRC:%.c=%.o)
CC = cc
CFLAGS = -g
RM = rm -f
HEADER = minishell.h

YELLOW = \033[1;33m
BLUE = \033[1;34m
RED = \033[1;31m
GREEN = \033[1;32m
PURPLE = \033[1;35m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline
	@echo "$(GREEN)Compilation successful √$(RESET)"

%.o: %.c $(HEADER)
	@echo "$(YELLOW)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Creating $@$(RESET)"

clean:
	@for obj in $(OBJS); do \
		if [ -f $$obj ]; then \
			echo "$(RED)Deleting $$obj$(RESET)"; \
			$(RM) $$obj; \
		fi \
	done

fclean: clean
	@if [ -f $(NAME) ]; then \
		echo "$(PURPLE)minishell deleted$(RESET)"; \
		$(RM) $(NAME); \
	fi

re: fclean all

.PHONY: all clean fclean re
