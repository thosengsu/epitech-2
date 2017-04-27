##
## Makefile for 205 in /home/erwan/Tek2/Math/205IQ
##
## Made by Erwan
## Login   <erwan.guiomar@epitech.eu>
##
## Started on  Wed Apr 12 11:00:08 2017 Erwan
## Last update Wed Apr 12 11:02:52 2017 Erwan
##

NAME		=	205IQ

SRCS		=	main.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	+=	-Wall -Werror -Wextra -e3

all: $(NAME)

$(NAME): $(OBJS)
	g++ -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
