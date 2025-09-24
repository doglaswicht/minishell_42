# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pedroribeiro <pedroribeiro@student.42.fr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 19:27:10 by procha-r          #+#    #+#              #
#    Updated: 2025/07/24 00:15:59 by pedroribeir      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                              MINISHELL MAKEFILE                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude -Isrc/libft -I/usr/include/readline
RM			= rm -f

# ======================================
#  LIBFT BUILD
# ======================================
LIBFT_DIR	= src/libft
LIBFT		= $(LIBFT_DIR)/libft.a

# ======================================
#  MANUAL LIST OF PROJECT FILES
# ======================================
SRCS	= \
	src/main/main.c \
	src/main/shell_loop.c \
	src/input/read_input.c \
	src/input/readline_config.c \
	src/input/prompt_init.c \
	src/input/prompt_utils.c \
	src/input/prompt_free.c \
	src/input/prompt_state.c \
	src/signals/signal_init.c \
	src/signals/signal_handlers.c \
	src/signals/signal_echoctl.c \
	src/signals/signal_global.c \
	src/tokenizer/tokenizer.c \
	src/tokenizer/token_utils.c \
	src/tokenizer/token_type.c \
	src/tokenizer/token_free.c \
	src/quotes/quote_check.c \
	src/quotes/quote_strip.c \
	src/quotes/quote_type.c \
	src/expansion/expand_main.c \
	src/expansion/expand_utils.c \
	src/expansion/expand_env.c \
	src/expansion/expand_exit.c \
	src/expansion/expand_char_helpers.c \
	src/expansion/expand_dollar_helpers.c \
	src/expansion/expand_loop.c \
	src/parser/ft_add_arg.c \
	src/parser/parser_main.c \
	src/parser/parser_main_utils.c \
	src/parser/parser_cmd.c \
	src/parser/parser_utils.c \
	src/parser/parser_split.c \
	src/redir/redir_main.c \
	src/redir/redir_input.c \
	src/redir/redir_output.c \
	src/redir/heredoc.c \
	src/redir/redir_apply.c \
	src/redir/redir_error.c \
	src/exec/exec_pipeline.c \
	src/exec/exec_pipeline_helpers.c \
	src/exec/exec_fork.c \
	src/exec/exec_utils.c \
	src/exec/exec_path.c \
	src/exec/pipes.c \
	src/exec/wait.c \
	src/exec/wait_utils.c \
	src/exec/exec_single.c \
	src/builtin/dispatcher.c \
	src/builtin/echo.c \
	src/builtin/cd.c \
	src/builtin/pwd.c \
	src/builtin/env.c \
	src/builtin/export.c \
	src/builtin/export_utils.c \
	src/builtin/unset.c \
	src/builtin/exit.c \
	src/env/env_init.c \
	src/env/env_helpers.c \
	src/env/env_get.c \
	src/env/env_set.c \
	src/env/env_unset.c \
	src/env/env_utils.c \
	src/env/env_to_str_array.c \
	src/env/env_free.c \
	src/utils/malloc_helpers.c \
	src/utils/str_utils.c \
	src/utils/cd_utils.c \
	src/utils/str_join.c \
	src/utils/free_utils.c \
	src/utils/error.c \
	src/cleanup/cleanup.c \
	src/cleanup/exit.c


OBJS	= $(SRCS:.c=.o)

# ======================================
#  RULES
# ======================================

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus