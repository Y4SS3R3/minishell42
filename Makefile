# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 09:40:06 by mzouine           #+#    #+#              #
#    Updated: 2024/09/08 08:22:36 by ymassiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = 	minishell.c \
		parsing/mz_arr.c \
		parsing/ft_list.c \
		parsing/mz_lexer.c \
		parsing/mz_split.c \
		parsing/mz_parser.c \
		parsing/mz_checker.c \
		execution/exec/env.c \
		parsing/mz_make_cmd.c \
		parsing/mz_last_scan.c \
		execution/tree/tree.c \
		execution/builtins/cd.c \
		parsing/lexer_utils1.c \
		parsing/lexer_utils2.c \
		execution/gc/gc_utils.c \
		execution/expanding/find_replace.c \
		parsing/mz_make_special.c\
		execution/builtins_utils/cd_utils.c\
		execution/builtins/pwd.c \
		execution/builtins/env.c \
		execution/exec/operands.c \
		execution/exec/pipeline.c \
		execution/exec/cmd_path.c \
		execution/builtins/echo.c \
		execution/builtins/exit.c \
		execution/builtins/unset.c \
		execution/builtins/export.c \
		execution/builtins_utils/cd_utils1.c \
		execution/exec/exec_utils1.c \
		execution/tree/redir_utils1.c \
		execution/general_utils/plus.c \
		execution/general_utils/utils1.c \
		execution/general_utils/utils2.c \
		execution/general_utils/utils3.c \
		execution/exec/cmd_redirs.c \
		parsing/env_parse.c \
		execution/expanding/remove_quotes.c \
		parsing/mz_splitter.c \
		execution/expanding/ex_hec_key1.c \
		parsing/mz_make_redi.c \
		parsing/mz_nul_split.c \
		execution/expanding/gnl.c \
		execution/gc/free_utils1.c \
		execution/general_utils/prompts.c \
		execution/expanding/expand.c \
		execution/fds/fds.c \
		execution/exec/dfs_tree.c \
		execution/fds/fildes.c \
		execution/tree/redir_utils2.c \
		execution/expanding/ex_hec_key.c \
		parsing/mz_key_assign.c \
		parsing/mz_utils.c \
		execution/wildcard/star_checkcmd.c \
		execution/expanding/gnl_utils.c \
		parsing/mz_joiner.c \
		execution/expanding/expand_redirs.c \
		execution/expanding/expand_arg.c \
		execution/exec/builtins_exec.c \
		execution/wildcard/matching.c \
		execution/wildcard/matching_utils.c \
		execution/wildcard/match_pattern.c \
		execution/exec/init_shell.c \
		execution/exec/heredoc.c \
		execution/expanding/expand_unit.c \
		execution/general_utils/[DEPRECATED]print_utils.c\
		execution/gc/free_utils.c \
		parsing/mz_syntax_bfr.c \
		parsing/mz_syntax_err.c \
		parsing/mz_syntax_err2.c \
		parsing/ft_itoa.c \
		execution/wildcard/matching_utils1.c \
		execution/expanding/expand_utils.c \
		parsing/mz_syntax_handler.c \
		parsing/mz_syntax_handler2.c \
		parsing/mz_key_assign2.c \
		parsing/mz_key_assign_utils.c \
		execution/exec/signals.c \
		execution/wildcard/star_checkredirs.c \
		execution/expanding/expand_cmd.c \
		execution/exec/heredoc1.c \
		execution/exec/exec_utils2.c \
		execution/expanding/remove_quotes_utils.c \
		execution/builtins_utils/export_utils3.c \
		execution/exec/heredoc2.c \
		execution/exec/cmd_redirs_utils.c \
		execution/expanding/expand_utils2.c \
		execution/builtins_utils/unset_utils.c \
		execution/exec/replace_key.c \
		execution/expanding/ym_arr_in.c \
		execution/wildcard/star_checkargs.c \
		execution/expanding/expand_utils1.c \
		execution/builtins_utils/export_utils.c \
		execution/builtins_utils/export_utils1.c \
		execution/expanding/ym_arr_rem.c \
		execution/general_utils/env_list.c \
		execution/general_utils/lst_manu1.c \
		execution/general_utils/utils4.c \
		execution/general_utils/utils5.c \
		execution/general_utils/utils6.c \
		execution/builtins_utils/export_utils2.c \
		execution/builtins_utils/export_utils4.c \
		execution/general_utils/utils7.c \
		execution/expanding/expand_unit_utils.c \
		execution/builtins_utils/export_utils5.c \
		execution/general_utils/lst_manu.c

OBJS = $(SRC:%.c=%.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -ggdb3 -g
RM = rm -f
HEADER = minishell.h
RLLIB1 = $(shell brew --prefix readline)/lib
RLINC1 = $(shell brew --prefix readline)/include

YELLOW = \033[1;33m
BLUE = \033[1;34m
RED = \033[1;31m
GREEN = \033[1;32m
PURPLE = \033[1;35m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L ${RLLIB1} -lreadline
	@echo "$(GREEN)Compilation successful √$(RESET)"

%.o: %.c $(HEADER)
	@echo "$(YELLOW)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) -I ${RLINC1} -c $< -o $@
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
