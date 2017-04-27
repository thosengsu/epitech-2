NAME		=	201yams

CPPFLAGS	=	-Wall -Wextra -Werror -std=c++14

SRCS		=	main.cc \
			check.cc \
			proba.cc \
			combination_fct.cc

OBJS		=	$(SRCS:.cc=.o)

RM		=	rm -f

all: $(NAME)

$(NAME): $(OBJS)
	g++ -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all $(NAME) clean fclean tr
