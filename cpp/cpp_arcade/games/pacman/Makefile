##
## Makefile for arcade in /home/erwan/Tek2/C++/cpp_arcade
##
## Made by Erwan
## Login   <erwan.guiomar@epitech.eu>
##
## Started on  Sun Apr  9 03:41:27 2017 Erwan
## Last update Sun Apr  9 18:23:04 2017 Erwan
##

NAME		=	pacman.so

CC		=	g++

RM		=	rm -f

CPPFLAGS	+=	-Werror -Wall -Wextra -fPIC -I../ -I../../includes -I../../dlLoader/
CPPFLAGS	+=	-I../../lib/

LDFLAGS		+=	-Wl,--no-undefined -lm -ldl -lpthread -lrt -shared

SRCS		=	Pacman.cpp \
			./../../dlLoader/dlGfxLoader.cpp

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME) $(NAMEA)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)
	cp $(NAME) ../$(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re: fclean all
