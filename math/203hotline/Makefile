##
## Makefile for 203 in /home/erwan/Tek2/Math/203hotline
##
## Made by Erwan
## Login   <erwan.guiomar@epitech.eu>
##
## Started on  Mon Mar 13 11:35:16 2017 Erwan
## Last update Thu Mar 23 10:19:10 2017 Erwan
##

NAME	=	203hotline

SRCS	=	checks.cpp \
		compute1.cpp \
		compute2.cpp \
		getArgs.cpp \
		main.cpp

OBJS	=	$(SRCS:.cpp=.o)

CPPFLAGS	+=	-Wall -Werror -Wextra -e3

all: $(NAME)

$(NAME): $(OBJS)
	g++ -o $(NAME) $(OBJS) -lgmpxx -lgmp -lm

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
