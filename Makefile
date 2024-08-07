CC					= cc
RM					= rm -f
CFLAGS				= -Wextra -Wall -Werror -g3
LDFLAGS				= -L./libft/printf/ -L./libft/ -lreadline -lncurses -lftprintf -lft
INCLUDE_PATH 		= ./includes/
MINISHELL_NAME 		= minishell
MINISHELL_SRCS		= ./parsing/tokenizer.c ./parsing/tokenizer_utils.c ./parsing/automate.c ./parsing/parsing.c \
					./parsing/parsing_utils.c ./parsing/debug_utils.c main.c ./builtin/print_env.c ./exec/env_utils.c \
					./exec/path.c
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

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(LIBFTPRINTF):
	@$(MAKE) -C $(LIBFTPRINTF_PATH)

clean:
				@$(RM) $(MINISHELL_OBJS)
				@$(MAKE) -C $(LIBFT_PATH) clean
				@$(MAKE) -C $(LIBFTPRINTF_PATH) clean

fclean:	 		clean
				@$(RM) $(MINISHELL_NAME)
				@$(MAKE) -C $(LIBFT_PATH) fclean
				@$(MAKE) -C $(LIBFTPRINTF_PATH) fclean

re:				fclean 
				@$(MAKE) all

.PHONY:			all clean fclean re