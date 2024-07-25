NAME = libftprintf.a
SRCS =  ft_printf.c nbrs.c puts.c

CC = gcc

FLAGS = -Wall -Wextra -Werror -Ofast -march=native

OBJS = $(SRCS:.c=.o)

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

all : $(NAME)

clean :
	@rm -rf $(SURPL_O) 
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean
	@$(MAKE) all

.PHONY:	all clean fclean re