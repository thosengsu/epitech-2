##
## Makefile for 205 in /home/erwan/Tek2/Math/205IQ/bonus
##
## Made by Erwan
## Login   <erwan.guiomar@epitech.eu>
##
## Started on  Fri Apr 14 13:19:25 2017 Erwan
## Last update Fri Apr 14 14:29:20 2017 Erwan
##

NAME		=	205IQ

CC		=	g++

RM		=	rm -f

SRCS		=	main.cpp

OBJS		=	$(SRCS:.cpp=.o)

LFLAGS		+=	-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lstdc++
LFLAGS		+=	-ldl -lm -L/home/$(USER)/.froot/lib/ -llapin

CPPFLAGS	+=	-Werror -Wall -Wextra -I../


all:	$(NAME)

${NAME}: $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
