##
## Makefile for arcade in /home/erwan/Tek2/C++/cpp_arcade/gfx_lib/Lapin
##
## Made by Erwan
## Login   <erwan.guiomar@epitech.eu>
##
## Started on  Thu Mar  9 16:54:50 2017 Erwan
## Last update Sun Apr  9 18:23:46 2017 Erwan
##

NAME		= lib_arcade_lapin.so

CC		= g++

RM		= rm -f

SRCS		= Lapin.cpp

OBJS		= $(SRCS:.cpp=.o)

LFLAGS		+= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lstdc++
LFLAGS		+= -ldl -lm -L/home/$(USER)/.froot/lib/ -llapin -shared

CPPFLAGS	+= -Werror -Wall -Wextra -I../ -fPIC


all:	$(NAME)

${NAME}: $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS)
	cp $(NAME) ../$(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re:	fclean all

.PHONY: all clean fclean re
