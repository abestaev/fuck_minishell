LIBC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
		ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_strcmp.c\
		ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c\

ADDITIONAL =	ft_itoa.c \
				ft_split.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c ft_striteri.c

BONUS =	ft_lstadd_back.c ft_lstadd_front.c ft_lstmap.c\
		ft_lstlast.c ft_lstclear.c ft_lstiter.c\
		ft_lstnew.c ft_lstsize.c ft_lstdelone.c\

SRCS = ${LIBC} ${ADDITIONAL} ${BONUS}

SRCSALL = ${LIBC} ${ADDITIONAL} ${BONUS}

OBJS = ${SRCS:.c=.o}

OBJSALL = ${SRCSALL:.c=.o} 

LIB = libft.a

CC = cc	

CFLAGS = -Wall -Werror -Wextra -I ./ -Ofast -march=native

.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${LIB}:	${OBJS}
		@ar -rsc ${LIB} ${OBJS}

bonus:	${OBJSALL}
		@ar -rsc ${LIB} $^

all: 	${LIB}

clean:	
		@rm -f ${OBJSALL}

fclean:	clean
		@rm -f ${LIB}

re:		fclean 
		@$(MAKE) all

so:
	@$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCSALL)
	@cc -nostartfiles -shared -o libft.so $(OBJSALL)

.PHONY: all clean fclean re bonus