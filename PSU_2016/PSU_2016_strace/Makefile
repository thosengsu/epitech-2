NAME			=	strace

CC			=	gcc

RM			=	rm -f

CFLAGS			+=	-W -Werror -Wall -Wextra

SRCS			=	main.c \
				access.c \
				execve.c \
				misc.c \
				mmap.c \
				mprotect.c \
				open.c \
				p_char_p.c \
				p_int.c \
				p_off_t.c \
				print.c \
				p_size_t.c \
				p_void_p.c \
				read.c \
				strace_prog.c \
				strace_pid.c \
				print_exit.c

OBJS			=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
