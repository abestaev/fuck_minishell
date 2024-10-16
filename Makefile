GREEN = \033[0;32m
RESET = \033[0m

CC					= cc
RM					= rm -f
CFLAGS				= -Wextra -Wall -Werror -g3
LDFLAGS				= -L./libft/printf/ -L./libft/ -lreadline -lncurses -lftprintf -lft
INCLUDE_PATH 		= ./includes/
MINISHELL_NAME 		= minishell
MINISHELL_SRCS		= ./parsing/tokenizer.c ./parsing/tokenizer_utils.c ./parsing/automate.c ./parsing/parsing.c \
					./parsing/parsing_utils.c ./parsing/debug_utils.c ./parsing/quote.c ./parsing/free.c \
					./exec/path.c ./exec/exec.c ./exec/builtin.c ./exec/redirection.c ./exec/heredoc.c \
					./expand/expand.c ./expand/expand_utils.c ./exec/pipe.c ./exec/exec2.c \
					./builtin/cd.c ./builtin/echo.c ./builtin/print_env.c ./builtin/export.c ./builtin/export_utils.c\
					./builtin/unset.c ./builtin/pwd.c ./builtin/exit.c ./exec/heredoc2.c \
					./env/copy_env.c ./env/env_utils.c \
					./signal/signal.c \
					main.c
MINISHELL_OBJS 		= $(MINISHELL_SRCS:.c=.o)

LIBFT_PATH = ./libft/
LIBFTPRINTF_PATH = ./libft/printf/

LIBFT = $(LIBFT_PATH)libft.a
LIBFTPRINTF = $(LIBFTPRINTF_PATH)libftprintf.a
MAKEFLAGS += --no-print-directory

all:			$(MINISHELL_NAME)

.c.o:
	@$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -c $< -o $(<:.c=.o)

$(MINISHELL_NAME):	$(MINISHELL_OBJS) $(LIBFT) $(LIBFTPRINTF)
					@$(CC) -o $(MINISHELL_NAME) $(MINISHELL_OBJS) $(CFLAGS) $(LDFLAGS) -I$(INCLUDE_PATH)
					@echo "$(GREEN)successfully compiled$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(LIBFTPRINTF):
	@$(MAKE) -C $(LIBFTPRINTF_PATH)

clean:
				@$(RM) $(MINISHELL_OBJS)
				@$(MAKE) -C $(LIBFT_PATH) clean
				@$(MAKE) -C $(LIBFTPRINTF_PATH) clean
				@echo "Object files cleaned"

fclean:	 		clean
				@$(RM) $(MINISHELL_NAME)
				@$(MAKE) -C $(LIBFT_PATH) fclean
				@$(MAKE) -C $(LIBFTPRINTF_PATH) fclean
				@echo "Executable $(NAME) removed"

re:				fclean 
				@$(MAKE) all

.PHONY:			all clean fclean re