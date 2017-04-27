NAME		=	202unsold

RM		=	rm -rf

CC		=	g++

CPPFLAGS	=	-Wall -Werror -Wextra

SRCS		=	checks.cc \
			help.cc \
			jointLaw.cc \
			main.cc \

OBJS		=	$(SRCS:.cc=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(SRCS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
