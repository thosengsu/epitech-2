##
## Makefile for 204 in /home/erwan/Tek2/Math/204ducks
##
## Made by Erwan
## Login   <erwan.guiomar@epitech.eu>
##
## Started on  Mon Mar 27 16:23:38 2017 Erwan
## Last update Mon Mar 27 16:23:39 2017 Erwan
##

NAME		=	204ducks

SRCS		=	main.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	+=	-Wall -Werror -Wextra -e3

all: $(NAME)

$(NAME): $(OBJS)
	g++ -o $(NAME) $(OBJS) -lgmpxx -lgmp -lm

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
