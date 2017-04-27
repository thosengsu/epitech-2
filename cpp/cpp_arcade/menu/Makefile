##
## Makefile for arcade in /home/erwan/Tek2/C++/cpp_arcade/menu
##
## Made by Erwan
## Login   <erwan.guiomar@epitech.eu>
##
## Started on  Sun Apr  9 03:37:09 2017 Erwan
## Last update Sun Apr  9 18:25:03 2017 Erwan
##

NAME		=	arcade

CC		=	g++

RM		=	rm -f

SRCS		=	main.cpp \
			Menu.cpp \
			../dlLoader/dlGameLoader.cpp \
			../dlLoader/dlGfxLoader.cpp

OBJS		=	$(SRCS:.cpp=.o)

LFLAGS		=	-ldl

CPPFLAGS	=	-Werror -Wall -Wextra -I../games -I../dlLoader -I../lib -I../includes

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS)
	cp ./$(NAME) ../

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME);

re: fclean all

.PHONY: all clean fclean
