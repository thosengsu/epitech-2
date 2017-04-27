NAME		=	ftrace

CC		=	gcc

RM		=	rm -f

CFLAGS		+=	-Iincludes/

SRCS		=	srcs/main.c \
			srcs/error.c \
			srcs/find_path.c \
			srcs/ftrace.c

OBJS		=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
