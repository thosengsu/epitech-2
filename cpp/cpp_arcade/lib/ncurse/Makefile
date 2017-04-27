##
## Makefile for arcade in /home/erwan/Tek2/C++/cpp_arcade
##
## Made by Erwan
## Login   <erwan.guiomar@epitech.eu>
##
## Started on  Sun Apr  9 18:24:24 2017 Erwan
## Last update Sun Apr  9 18:24:29 2017 Erwan
##

NAME		=	lib_arcade_ncurse.so

RM		=	rm -f

CC		=	g++

CPPFLAGS	+=	-Wall -Werror -Wextra -fPIC -I/usr/include/ncurses -I../ -D_REENTRANT -g3

LDFLAGS		+=	-shared -L/usr/lib -lncurses -L/usr/lib -lncurses -Wl,--no-undefined -lm
LDFLAGS		+=	-ldl -lpthread -lrt

SRCS		=	ncurses.cpp

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)
	cp $(NAME) ../

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re: fclean all
